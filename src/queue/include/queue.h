//
// Created by w1ckedente on 21.03.2021.
//

#ifndef TEMPLATE_QUEUE_H
#define TEMPLATE_QUEUE_H

#include <stddef.h>

typedef struct queue queue_t;

queue_t *init_queue();

int enqueue(queue_t *queue, void *value);

void *dequeue(queue_t *queue);

size_t queue_size(queue_t *queue);

void free_queue(queue_t *queue);

#endif  // TEMPLATE_QUEUE_H
