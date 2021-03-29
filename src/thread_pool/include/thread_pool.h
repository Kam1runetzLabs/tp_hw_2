// Copyright 2021 Kam1runetzLabs <notsoserious2017@gmail.com>

#ifndef THREAD_POOL_INCLUDE_THREAD_POOL_H_
#define THREAD_POOL_INCLUDE_THREAD_POOL_H_

#include <stddef.h>

typedef struct thread_pool thread_pool_t;

typedef void *(*task_t)(void *);
typedef void (*callback_t)(void *);

///@return количество физически поддерживаемых конкурирующих потоков, -1 в
///случае ошибки
long hardware_concurrency();

///@brief инициализирует пул и запускает рабочие потоки
///@param workers_count количество рабочих потоков
///@return указатель на инициализированный пул или NULL в случае ошибки
thread_pool_t *thread_pool_init(size_t workers_count);

///@brief добавляет задачу в очередь на выполнение
///@param pool указатель на пул, не может быть NULL
///@param task указатель на рабочую функцию, может быть NULL
///@param args указатель на массив аргументов для рабочей функции, может быть
/// NULL
///@param callback указатель на функцию обратного вызова, может быть NULL, тогда
///отработает только функция task
///@return -1 в случае ошибки, 0 в случае успеха
int thread_pool_enqueue_task(thread_pool_t *pool, task_t task, void *args,
                             callback_t callback);

///@brief блокирует вызывающий поток, пока не выполнятся все задачи, затем
///разрушает пул и освобождает ресурсы
///@param pool указатель на пул, не может быт NULL
void thread_pool_wait_and_destroy(thread_pool_t *pool);

///@brief блокирует вызывающий поток, пока не выполнятся текущие задачи, затем
///разрушает пул и освобождает ресурсы
///@param pool указатель на пул, не может быть NULL
void thread_pool_cancel_and_destroy(thread_pool_t *pool);

#endif  // THREAD_POOL_INCLUDE_THREAD_POOL_H_
