//
// Created by w1ckedente on 21.03.2021.
//

#ifndef TEMPLATE_THREAD_POOL_H
#define TEMPLATE_THREAD_POOL_H

#include <stddef.h>

typedef struct thread_pool thread_pool_t;

typedef void *(*task_t)(void *);
typedef void (*callback_t)(void *);

thread_pool_t *init_thread_pool(size_t workers_count);

int enqueue_task(thread_pool_t *tp, task_t task, void *args,
                 callback_t callback);

void wait_thread_pool(thread_pool_t *tp);

void destroy_thread_pool(thread_pool_t *tp);

#endif  // TEMPLATE_THREAD_POOL_H
