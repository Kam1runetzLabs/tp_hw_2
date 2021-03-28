// Copyright 2021 Kam1runetzLabs <notsoserious2017@gmail.com>

#include <assert.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#include "thread_pool.h"
#include "queue.h"

#define PTHREAD_SAFE_INIT(pool, statement) \
  {                                        \
    int error = statement;                 \
    if (error) {                           \
      thread_pool_free(pool);              \
      return NULL;                         \
    }                                      \
  }

typedef enum {
  THREAD_POOL_WORK,
  THREAD_POOL_WAIT,
  THREAD_POOL_CANCEL
} thread_pool_flags_t;

typedef struct {
  task_t task;
  void *task_args;
  callback_t callback;
} job_t;

struct thread_pool {
  pthread_mutex_t mutex;
  pthread_attr_t attr;
  pthread_cond_t work_cv;
  pthread_cond_t wait_cv;
  pthread_cond_t cancel_cv;
  queue_t *jobs_queue;
  size_t workers_count;
  thread_pool_flags_t flag;
};

static job_t *job_init(task_t task, void *args, callback_t cb);
static void job_run(job_t *job);
static void *thread_routine(void *arg);
static void thread_pool_free(thread_pool_t *pool);

long hardware_concurrency() { return sysconf(_SC_NPROCESSORS_ONLN); }

thread_pool_t *thread_pool_init(size_t workers_count) {
  assert(workers_count != 0);

  thread_pool_t *pool = (thread_pool_t *)malloc(sizeof(thread_pool_t));
  if (!pool) return NULL;

  PTHREAD_SAFE_INIT(pool, pthread_mutex_init(&pool->mutex, NULL));
  PTHREAD_SAFE_INIT(pool, pthread_attr_init(&pool->attr));
  PTHREAD_SAFE_INIT(pool, pthread_cond_init(&pool->work_cv, NULL));
  PTHREAD_SAFE_INIT(pool, pthread_cond_init(&pool->wait_cv, NULL));
  PTHREAD_SAFE_INIT(pool, pthread_cond_init(&pool->cancel_cv, NULL));

  pool->jobs_queue = queue_init();
  if (!pool->jobs_queue) {
    thread_pool_free(pool);
    return NULL;
  }

  pthread_attr_setdetachstate(&pool->attr, PTHREAD_CREATE_DETACHED);

  pthread_mutex_lock(&pool->mutex);
  for (size_t i = 0; i != workers_count; ++i) {
    pthread_t tid;
    pthread_create(&tid, &pool->attr, thread_routine, pool);
  }
  pool->workers_count = workers_count;
  pool->flag = THREAD_POOL_WORK;
  pthread_mutex_unlock(&pool->mutex);
  return pool;
}

int thread_pool_enqueue_task(thread_pool_t *pool, task_t task, void *args,
                             callback_t callback) {
  assert(pool != NULL && task != NULL);

  job_t *job = job_init(task, args, callback);
  if (!job) return -1;

  pthread_mutex_lock(&pool->mutex);
  int error = queue_push(pool->jobs_queue, job);
  if (error) {
    pthread_mutex_unlock(&pool->mutex);
    return -1;
  }
  pthread_cond_signal(&pool->work_cv);
  pthread_mutex_unlock(&pool->mutex);
  return 0;
}

void thread_pool_wait_and_destroy(thread_pool_t *pool) {
  assert(pool != NULL);
  pthread_mutex_lock(&pool->mutex);
  pool->flag = THREAD_POOL_WAIT;
  pthread_cond_broadcast(&pool->work_cv);
  while (!queue_empty(pool->jobs_queue))
    pthread_cond_wait(&pool->wait_cv, &pool->mutex);
  pthread_mutex_unlock(&pool->mutex);
  thread_pool_free(pool);
}

void thread_pool_cancel_and_destroy(thread_pool_t *pool) {
  assert(pool != NULL);
  pthread_mutex_lock(&pool->mutex);
  pool->flag = THREAD_POOL_CANCEL;
  pthread_cond_broadcast(&pool->work_cv);
  while (pool->workers_count > 0)
    pthread_cond_wait(&pool->cancel_cv, &pool->mutex);
  pthread_mutex_unlock(&pool->mutex);
  thread_pool_free(pool);
}

static job_t *job_init(task_t task, void *args, callback_t cb) {
  job_t *job = (job_t *)malloc(sizeof(job_t));
  if (!job) return NULL;

  job->task = task;
  job->task_args = args;
  job->callback = cb;
  return job;
}

static void job_run(job_t *job) {
  if (job->callback)
    job->callback(job->task(job->task_args));
  else
    job->task(job->task_args);
}

static void *thread_routine(void *arg) {
  thread_pool_t *pool = (thread_pool_t *)arg;

  pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
  pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);

  pthread_mutex_lock(&pool->mutex);
  for (;;) {
    while (queue_empty(pool->jobs_queue) && pool->flag != THREAD_POOL_CANCEL)
      pthread_cond_wait(&pool->work_cv, &pool->mutex);

    if (pool->flag == THREAD_POOL_CANCEL) break;

    if (!queue_empty(pool->jobs_queue)) {
      job_t *job = queue_pop(pool->jobs_queue);
      pthread_mutex_unlock(&pool->mutex);

      job_run(job);
      free(job);

      pthread_mutex_lock(&pool->mutex);
    }

    if (pool->flag == THREAD_POOL_WAIT && queue_empty(pool->jobs_queue)) {
      pthread_cond_broadcast(&pool->wait_cv);
      break;
    }
  }

  if (--pool->workers_count == 0) pthread_cond_broadcast(&pool->cancel_cv);
  pthread_mutex_unlock(&pool->mutex);
  pthread_exit(NULL);
}

static void thread_pool_free(thread_pool_t *pool) {
  pthread_mutex_destroy(&pool->mutex);
  pthread_attr_destroy(&pool->attr);
  pthread_cond_destroy(&pool->work_cv);
  pthread_cond_destroy(&pool->wait_cv);
  pthread_cond_destroy(&pool->cancel_cv);

  while (!queue_empty(pool->jobs_queue)) {
    job_t *job = queue_pop(pool->jobs_queue);
    free(job);
  }

  queue_free(pool->jobs_queue);
  free(pool);
}
