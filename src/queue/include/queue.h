// Copyright 2021 Kam1runetzLabs <notsoserious2017@gmail.com>

#ifndef QUEUE_INCLUDE_QUEUE_H_
#define QUEUE_INCLUDE_QUEUE_H_

#include <stdbool.h>
#include <stddef.h>

typedef struct queue queue_t;

///@brief инициализирует пустую очередь
///@return указатель на созданную очередь или NULL в случае ошибки
queue_t *queue_init();

///@param queue указатель на очередь, не должен быть NULL
///@param value добавляемый элемент, может принимать любое значение
///@return 0 в случае успешного выполнения, -1 в случае ошибки
int queue_push(queue_t *queue, void *value);

///@param queue указатель на очередь, не должен быть NULL
///@param element указатель, в который будет помещено вынимаемое значение
///@return 0 в случае успеха, -1 в случае ошибки
int queue_pop(queue_t *queue, void **element);

///@param queue указатель на очередь, не должен быть NULL
///@return размер очереди, 0 в случае если очередь пуста или передан NULL
size_t queue_size(const queue_t *queue);

///@param queue указатель на очередь, не должен быть NULL
///@return true если очередь пуста или передан NULL, иначе false
bool queue_empty(const queue_t *queue);

///@param queue указатель на удаляемую очередь, может быть NULL
void queue_free(queue_t *queue);

#endif  // QUEUE_INCLUDE_QUEUE_H_
