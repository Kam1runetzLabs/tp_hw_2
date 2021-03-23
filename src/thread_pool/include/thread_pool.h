//
// Created by w1ckedente on 21.03.2021.
//

#ifndef TEMPLATE_THREAD_POOL_H
#define TEMPLATE_THREAD_POOL_H

#include <stddef.h>

typedef struct thread_pool thread_pool_t;

typedef void *(*task_t)(void *);
typedef void (*callback_t)(void *);

thread_pool_t *init_thread_pool(size_t min_thr_count, size_t max_thr_count,
                                size_t ttl);

int enqueue_task(thread_pool_t *pool, task_t task, void *args,
                 callback_t callback);

void wait_thread_pool(thread_pool_t *pool);

void destroy_thread_pool(thread_pool_t *pool);

#endif  // TEMPLATE_THREAD_POOL_H
