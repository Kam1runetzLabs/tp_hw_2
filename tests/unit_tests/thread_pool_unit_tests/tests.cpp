// Copyright 2021 Kam1runetzLabs <notsoserious2017@gmail.com>

#include <gtest/gtest.h>

extern "C" {
#include "thread_pool.h"
}

TEST(ThreadPoolInit, ThreadPoolInit) {
  thread_pool_t *pool = thread_pool_init(hardware_concurrency());
  EXPECT_TRUE(pool);
  thread_pool_cancel_and_destroy(pool);
}

TEST(ThreadPoolInit, ThreadPoolInitWithNullThreadsCount) {
  EXPECT_EXIT(thread_pool_init(0), ::testing::KilledBySignal(SIGABRT), "");
}

void *task(void *arg) {
  if (!arg) return nullptr;
  int *number = (int *)arg;
  *number *= *number;
  return nullptr;
}

TEST(ThreadPoolEnqueueTask, ThreadPoolEnqueueTaskAndWaitTasks) {
  const size_t numbers_count = 12;
  int numbers[numbers_count];
  for (size_t i = 0; i != numbers_count; ++i) numbers[i] = i;

  thread_pool_t *pool = thread_pool_init(hardware_concurrency());
  for (size_t i = 0; i != numbers_count; ++i)
    thread_pool_enqueue_task(pool, task, &(numbers[i]), nullptr);
  thread_pool_wait_and_destroy(pool);
  for (size_t i = 0; i != numbers_count; ++i) EXPECT_EQ(numbers[i], i * i);
}

TEST(ThreadPoolEnqueueTask, ThreadPoolEnqueueToNullPool) {
  thread_pool_t *pool = nullptr;
  EXPECT_EXIT(thread_pool_enqueue_task(pool, task, nullptr, nullptr),
              ::testing::KilledBySignal(SIGABRT), "");
}

TEST(ThreadPoolWaitAndDestroy, WaitAndDestroyNullPool) {
  thread_pool_t *pool = nullptr;
  EXPECT_EXIT(thread_pool_wait_and_destroy(pool),
              ::testing::KilledBySignal(SIGABRT), "");
}

TEST(ThreadPoolCancelAndDestroy, CancelAndDestroyNullPool) {
  thread_pool_t *pool = nullptr;
  EXPECT_EXIT(thread_pool_cancel_and_destroy(pool),
              ::testing::KilledBySignal(SIGABRT), "");
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  testing::FLAGS_gtest_death_test_style = "threadsafe";
  return RUN_ALL_TESTS();
}
