//
// Created by w1ckedente on 21.03.2021.
//

#ifndef TEMPLATE_THREAD_POOL_H
#define TEMPLATE_THREAD_POOL_H

#include <stddef.h>

typedef struct thread_pool thread_pool_t;

typedef void *(*task_t)(void *);
typedef void (*callback_t)(void *);

long long hardware_concurrency();

thread_pool_t *thread_pool_init(size_t workers_count);

int thread_pool_enqueue_task(thread_pool_t *pool, task_t task, void *args,
                             callback_t callback);

void thread_pool_wait_and_destroy(thread_pool_t *pool);

void thread_pool_cancel_and_destroy(thread_pool_t *pool);

#endif  // TEMPLATE_THREAD_POOL_H
