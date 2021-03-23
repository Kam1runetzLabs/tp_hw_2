//
// Created by w1ckedente on 21.03.2021.
//

#include "thread_pool.h"

#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "queue.h"

#define POOL_WAIT 1
#define POOL_DESTROY 2

#define SAFE_PTHREAD_INIT(pool, init_foo) \
  {                                       \
    int error = init_foo;                 \
    if (error) {                          \
      free_pool(pool);                    \
      return NULL;                        \
    }                                     \
  }

typedef struct active {
  struct active *next;
  pthread_t tid;
} active_t;

typedef struct job {
  task_t task;
  void *args;
  callback_t callback;
} job_t;

struct thread_pool {
  pthread_mutex_t mutex;
  pthread_cond_t thr_work_cv;
  pthread_cond_t thr_wait_cv;
  pthread_cond_t thr_end_cv;
  pthread_attr_t attr;
  queue_t *jobs;
  active_t *active;
  size_t max_threads_count;
  size_t min_threads_count;
  size_t cur_threads_count;
  size_t idle_threads_count;
  size_t ttl;
  int flags;
};

static job_t *init_job(task_t task, void *args, callback_t cb);
static void run_job(job_t *job);
static void *worker_thread(void *arg);
static int create_worker(thread_pool_t *pool);
static void worker_cleanup(thread_pool_t *pool);
static void job_cleanup(thread_pool_t *pool);
static void notify_waiters(thread_pool_t *pool);
static void free_pool(thread_pool_t *pool);

thread_pool_t *init_thread_pool(size_t min_thr_count, size_t max_thr_count,
                                size_t ttl) {
  assert(min_thr_count > 0);
  assert(max_thr_count > min_thr_count);

  thread_pool_t *pool = (thread_pool_t *)malloc(sizeof(thread_pool_t));
  if (!pool) return NULL;

  SAFE_PTHREAD_INIT(pool, pthread_mutex_init(&pool->mutex, NULL));
  SAFE_PTHREAD_INIT(pool, pthread_cond_init(&pool->thr_work_cv, NULL));
  SAFE_PTHREAD_INIT(pool, pthread_cond_init(&pool->thr_wait_cv, NULL));
  SAFE_PTHREAD_INIT(pool, pthread_cond_init(&pool->thr_end_cv, NULL));
  SAFE_PTHREAD_INIT(pool, pthread_attr_init(&pool->attr));

  SAFE_PTHREAD_INIT(
      pool, pthread_attr_setdetachstate(&pool->attr, PTHREAD_CREATE_DETACHED));

  pool->jobs = init_queue();
  if (!pool->jobs) {
    free_pool(pool);
    return NULL;
  }

  pool->active = NULL;
  pool->max_threads_count = max_thr_count;
  pool->min_threads_count = min_thr_count;
  pool->cur_threads_count = 0;
  pool->idle_threads_count = 0;
  pool->ttl = ttl;
  pool->flags = 0;

  return pool;
}

int enqueue_task(thread_pool_t *pool, task_t task, void *args,
                 callback_t callback) {
  assert(pool != NULL);
  assert(task != NULL);

  job_t *job = init_job(task, args, callback);
  if (!job) return -1;

  pthread_mutex_lock(&pool->mutex);
  int error = enqueue(pool->jobs, job);
  if (error) {
    pthread_mutex_unlock(&pool->mutex);
    return error;
  }

  if (pool->idle_threads_count > 0) {
    pthread_cond_signal(&pool->thr_work_cv);
  } else if (pool->cur_threads_count < pool->max_threads_count &&
             create_worker(pool) == 0) {
    ++pool->cur_threads_count;
  }

  pthread_mutex_unlock(&pool->mutex);
  return 0;
}

void wait_thread_pool(thread_pool_t *pool) {
  assert(pool != NULL);
  pthread_mutex_lock(&pool->mutex);
  while (!queue_empty(pool->jobs) || pool->active != NULL) {
    pool->flags |= POOL_WAIT;
    pthread_cond_wait(&pool->thr_wait_cv, &pool->mutex);
  }
  pthread_mutex_unlock(&pool->mutex);
}

void destroy_thread_pool(thread_pool_t *pool) {
  if (!pool) return;
  active_t *active;

  pthread_mutex_lock(&pool->mutex);

  pool->flags |= POOL_DESTROY;
  pthread_cond_broadcast(&pool->thr_work_cv);

  for (active = pool->active; active != NULL; active = active->next)
    if (active->tid) pthread_cancel(active->tid);
  printf("threads canceled\n");

  while (pool->active != NULL) {
    printf("%p\n", (void *)pool->active);
    pool->flags |= POOL_WAIT;
    pthread_cond_wait(&pool->thr_wait_cv, &pool->mutex);
    printf("signal received\n");
  }

  while (pool->cur_threads_count != 0)
    pthread_cond_wait(&pool->thr_end_cv, &pool->mutex);
  pthread_mutex_unlock(&pool->mutex);

  free_pool(pool);
}

static job_t *init_job(task_t task, void *args, callback_t cb) {
  job_t *job = (job_t *)malloc(sizeof(job_t));
  if (!job) return NULL;

  job->task = task;
  job->args = args;
  job->callback = cb;
  return job;
}

static void run_job(job_t *job) {
  if (job->callback)
    job->callback(job->task(job->args));
  else
    job->task(job->args);
}

static void *worker_thread(void *arg) {
  thread_pool_t *pool = (thread_pool_t *)arg;
  struct timespec ts;
  active_t active;

  pthread_mutex_lock(&pool->mutex);
  for (;;) {
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);

    pool->idle_threads_count++;
    if (pool->flags & POOL_WAIT) notify_waiters(pool);
    while (queue_empty(pool->jobs) && !(pool->flags & POOL_DESTROY)) {
      if (pool->cur_threads_count <= pool->min_threads_count) {
        pthread_cond_wait(&pool->thr_work_cv, &pool->mutex);
      } else {
        clock_gettime(CLOCK_REALTIME, &ts);
        ts.tv_sec += pool->ttl;
        if (pool->ttl == 0 ||
            pthread_cond_timedwait(&pool->thr_work_cv, &pool->mutex, &ts) ==
                ETIMEDOUT) {
          break;
        }
      }
    }

    pool->idle_threads_count--;
    if (pool->flags & POOL_DESTROY) break;
    job_t *job;
    if (!queue_empty(pool->jobs)) {
      active.next = pool->active;
      job = dequeue(pool->jobs);
      pool->active = &active;
      pthread_mutex_unlock(&pool->mutex);

      run_job(job);
      free(job);
      pthread_mutex_lock(&pool->mutex);
      job_cleanup(pool);
    }
    if (pool->flags & POOL_WAIT) notify_waiters(pool);
    pthread_mutex_unlock(&pool->mutex);
  }

  if (pool->flags & POOL_WAIT) notify_waiters(pool);
  worker_cleanup(pool);
  pthread_mutex_unlock(&pool->mutex);
  return NULL;
}

static int create_worker(thread_pool_t *pool) {
  int error;
  pthread_t tid;
  error = pthread_create(&tid, &pool->attr, worker_thread, pool);
  return error;
}

static void worker_cleanup(thread_pool_t *pool) {
  --pool->cur_threads_count;
  if (pool->flags & POOL_DESTROY) {
    if (pool->cur_threads_count == 0) pthread_cond_broadcast(&pool->thr_end_cv);
  } else if (pool->cur_threads_count < pool->min_threads_count &&
             create_worker(pool) == 0) {
    pool->cur_threads_count++;
  }
}

static void job_cleanup(thread_pool_t *pool) {
  pthread_t tid = pthread_self();
  active_t *activep;
  active_t **activepp;

  for (activepp = &pool->active; (activep = *activepp) != NULL;
       *activepp = activep->next) {
    if (activep->tid == tid) {
      *activepp = activep->next;
      break;
    }
  }
}

static void notify_waiters(thread_pool_t *pool) {
  if (pool->active == NULL && queue_empty(pool->jobs)) {
    pool->flags &= ~POOL_WAIT;
    pthread_cond_broadcast(&pool->thr_wait_cv);
  }
}

static void free_pool(thread_pool_t *pool) {
  pthread_mutex_destroy(&pool->mutex);
  pthread_cond_destroy(&pool->thr_work_cv);
  pthread_cond_destroy(&pool->thr_wait_cv);
  pthread_cond_destroy(&pool->thr_end_cv);
  pthread_attr_destroy(&pool->attr);

  if (pool->jobs) {
    while (!queue_empty(pool->jobs)) {
      job_t *job = dequeue(pool->jobs);
      free(job);
    }
  }

  free_queue(pool->jobs);
  free(pool);
}
