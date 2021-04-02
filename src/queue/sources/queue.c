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

queue_t *queue_init() {
  queue_t *queue = (queue_t *)malloc(sizeof(queue_t));
  if (!queue) return NULL;
  queue->head = queue->tail = NULL;
  queue->size = 0;
  return queue;
}

int queue_push(queue_t *queue, void *value) {
  if (!queue) return -1;

  node_t *new_node = (node_t *)malloc(sizeof(node_t));
  if (!new_node) return -1;

  new_node->next = NULL;
  new_node->value = value;

  if (!queue->head) {
    queue->head = queue->tail = new_node;
  } else {
    queue->tail->next = new_node;
    queue->tail = new_node;
  }

  ++queue->size;
  return 0;
}

int queue_pop(queue_t *queue, void **element) {
  if (!queue || !element) return -1;
  if (!queue->head) return -1;

  node_t *tmp_head = queue->head;
  *element = tmp_head->value;
  queue->head = queue->head->next;
  free(tmp_head);
  --queue->size;
  return 0;
}

size_t queue_size(const queue_t *queue) {
  if (!queue) return 0;
  return queue->size;
}

bool queue_empty(const queue_t *queue) {
  if (!queue) return true;
  return queue->size == 0;
}

void queue_free(queue_t *queue) {
  if (!queue) return;

  for (node_t *tmp = queue->head; tmp != NULL; tmp = queue->head) {
    queue->head = tmp->next;
    free(tmp);
  }

  free(queue);
}
