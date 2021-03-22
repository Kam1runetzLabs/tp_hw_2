// Copyright 2021 Kam1runetzLabs <notsoserious2017@gmail.com>

#include "queue.h"

#include <assert.h>
#include <malloc.h>
#include <stddef.h>

typedef struct node {
  struct node *next;
  void *value;
} node_t;

struct queue {
  node_t *head;
  node_t *tail;
  size_t size;
};

queue_t *init_queue() {
  queue_t *queue = (queue_t *)malloc(sizeof(queue_t));
  if (!queue) return NULL;
  queue->head = queue->tail = NULL;
  queue->size = 0;
  return queue;
}

int enqueue(queue_t *queue, void *value) {
  assert(queue != NULL);

  node_t *new_node = (node_t *)malloc(sizeof(node_t));
  if (!new_node) return -1;

  new_node->next = NULL;
  new_node->value = value;

  if (queue->tail) {
    queue->tail->next = new_node;
    queue->tail = new_node;
  } else {
    queue->head = queue->tail = new_node;
  }

  ++queue->size;
  return 0;
}

void *dequeue(queue_t *queue) {
  assert(queue != NULL);
  assert(queue->head != NULL);

  void *ret_value = queue->head->value;
  node_t *tmp_head = queue->head;
  queue->head = queue->head->next;
  free(tmp_head);
  --queue->size;
  return ret_value;
}

size_t queue_size(const queue_t *queue) {
  assert(queue != NULL);
  return queue->size;
}

bool queue_empty(const queue_t *queue) {
  assert(queue != NULL);
  return queue->head == NULL;
}

void free_queue(queue_t *queue) {
  if (!queue) return;

  for (node_t *tmp = queue->head; tmp != NULL; tmp = queue->head) {
    queue->head = tmp->next;
    free(tmp);
  }

  free(queue);
}
