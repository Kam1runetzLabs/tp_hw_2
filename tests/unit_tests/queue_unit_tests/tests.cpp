// Copyright 2021 Kam1runetzLabs <notsoserious2017@gmail.com>

#include <gtest/gtest.h>

extern "C" {
#include "queue.h"
}

const size_t kElementsCount = 123;

TEST(QueueInit, QueueInit) {
  queue_t *queue = queue_init();
  EXPECT_TRUE(queue);
  queue_free(queue);
}

TEST(QueueEmptyPred, QueueEmptyPred) {
  queue_t *queue = queue_init();
  EXPECT_TRUE(queue_empty(queue));
  queue_free(queue);
}

TEST(QueueEmptyPred, NullQueueEmptyPred) {
  queue_t *queue = nullptr;
  EXPECT_TRUE(queue_empty(queue));
}

TEST(QueuePush, PushToQueue) {
  queue_t *queue = queue_init();
  int value = 123;
  int error = queue_push(queue, &value);
  EXPECT_FALSE(error);
  EXPECT_FALSE(queue_empty(queue));
  queue_free(queue);
}

TEST(QueuePush, PushToNullQueue) {
  int value = 123;
  queue_t *queue = nullptr;
  int error = queue_push(queue, &value);
  EXPECT_TRUE(error);
}

TEST(QueuePop, PopFromQueue) {
  queue_t *queue = queue_init();
  int elements[kElementsCount];
  for (size_t i = 0; i != kElementsCount; ++i) queue_push(queue, &elements[i]);
  for (size_t i = 0; i != kElementsCount; ++i) {
    int *element_ptr;
    queue_pop(queue, (void **)&element_ptr);
    EXPECT_EQ(*element_ptr, elements[i]);
  }
}

TEST(QueuePop, PopFromNullQueue) {
  queue_t *queue = nullptr;
  void *element;
  int error = queue_pop(queue, (void **)&element);
  EXPECT_TRUE(error);
}

TEST(QueuePop, PopFromEmptyQueue) {
  queue_t *queue = queue_init();
  EXPECT_TRUE(queue_empty(queue));
  void *element;
  int error = queue_pop(queue, &element);
  EXPECT_TRUE(error);
  queue_free(queue);
}

TEST(QueuePop, PopToNullElementPtr) {
  queue_t *queue = queue_init();
  int element = 123;
  queue_push(queue, &element);
  int error = queue_pop(queue, NULL);
  EXPECT_TRUE(error);
  queue_free(queue);
}

TEST(QueueSizeGetter, GettingQueueSize) {
  queue_t *queue = queue_init();
  int elements[kElementsCount];
  for (size_t i = 0; i != kElementsCount; ++i) queue_push(queue, &elements[i]);
  EXPECT_EQ(kElementsCount, queue_size(queue));
  queue_free(queue);
}

TEST(QueueSizeGetter, GettingNullQueueSize) {
  queue_t *queue = nullptr;
  size_t size = queue_size(queue);
  EXPECT_EQ(size, 0);
}
