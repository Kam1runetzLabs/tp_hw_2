//
// Created by w1ckedente on 21.03.2021.
//

#ifndef TEMPLATE_QUEUE_H
#define TEMPLATE_QUEUE_H

#include <stdbool.h>
#include <stddef.h>

typedef struct queue queue_t;

///@brief инициализирует пустую очередь
///@return указатель на созданную очередь или NULL в случае ошибки
queue_t *init_queue();

///@param queue указатель на очередь, не должен быть NULL
///@param value добавляемый элемент, может принимать любое значение
///@return 0 в случае успешного выполнения, -1 в случае ошибки
int enqueue(queue_t *queue, void *value);

///@param queue указатель на очередь, не должен быть NULL
///@return первый элемент очереди или NULL если очередь пуста или не
///инициализированна
void *dequeue(queue_t *queue);

///@param queue указатель на очередь, не должен быть NULL
///@return размер очереди
size_t size_queue(const queue_t *queue);

///@param queue указатель на очередь, не должен быть NULL
///@return true если очередь пуста или неинициализированна, иначе false
bool empty_queue(const queue_t *queue);

///@param queue указатель на удаляемую очередь, может быть NULL
void free_queue(queue_t *queue);

#endif  // TEMPLATE_QUEUE_H
