
#include "queue.h"

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
  if (!queue) return -1;

  node_t *tmp = (node_t *)malloc(sizeof(node_t));
  if (!tmp) return -1;

  tmp->next = NULL;
  tmp->value = value;

  if (queue->tail) {
    queue->tail->next = tmp;
    queue->tail = tmp;
  } else {
    queue->head = queue->tail = tmp;
  }

  ++queue->size;
  return 0;
}

void *dequeue(queue_t *queue) {
  if (!queue) return NULL;
  if (!queue->head) return NULL;

  void *ret_value = queue->head->value;
  node_t *tmp_head = queue->head;
  queue->head = queue->head->next;
  free(tmp_head);
  --queue->size;
  return ret_value;
}

size_t queue_size(queue_t *queue) { return queue->size; }

void free_queue(queue_t *queue) {
  if (!queue) return;
  if (!queue->head) return;
  while (queue->head) {
    node_t *tmp_head = queue->head;
    queue->head = queue->head->next;
    free(tmp_head);
  }
}
