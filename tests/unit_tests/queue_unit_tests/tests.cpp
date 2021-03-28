// Copyright 2021 Kam1runetzLabs <notsoserious2017@gmail.com>

#include <gtest/gtest.h>

extern "C" {
#include "queue.h"
}

const size_t elements_count = 123;

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
  EXPECT_EXIT(queue_empty(queue), ::testing::KilledBySignal(SIGABRT), "");
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
  EXPECT_EXIT(queue_push(queue, &value), ::testing::KilledBySignal(SIGABRT),
              "");
}

TEST(QueuePop, PopFromQueue) {
  queue_t *queue = queue_init();
  int elements[elements_count];
  for (size_t i = 0; i != elements_count; ++i) queue_push(queue, &elements[i]);
  for (size_t i = 0; i != elements_count; ++i) {
    int *element_ptr = (int *)queue_pop(queue);
    EXPECT_EQ(*element_ptr, elements[i]);
  }
}

TEST(QueuePop, PopFromNullQueue) {
  queue_t *queue = nullptr;
  EXPECT_EXIT(queue_pop(queue), ::testing::KilledBySignal(SIGABRT), "");
}

TEST(QueuePop, PopFromEmptyQueue) {
  queue_t *queue = queue_init();
  EXPECT_TRUE(queue_empty(queue));
  EXPECT_EXIT(queue_pop(queue), ::testing::KilledBySignal(SIGABRT), "");
  queue_free(queue);
}

TEST(QueueSizeGetter, GettingQueueSize) {
  queue_t *queue = queue_init();
  int elements[elements_count];
  for (size_t i = 0; i != elements_count; ++i) queue_push(queue, &elements[i]);
  EXPECT_EQ(elements_count, queue_size(queue));
  queue_free(queue);
}

TEST(QueueSizeGetter, GettingNullQueueSize) {
  queue_t *queue = nullptr;
  EXPECT_EXIT(queue_size(queue), ::testing::KilledBySignal(SIGABRT), "");
}
