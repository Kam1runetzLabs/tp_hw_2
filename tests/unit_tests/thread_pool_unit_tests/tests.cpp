// Copyright 2021 Kam1runetzLabs <notsoserious2017@gmail.com>

#include <gtest/gtest.h>
#include <unistd.h>

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
  return number;
}

const size_t kNumbersCount = 12;
TEST(ThreadPoolEnqueueTask, ThreadPoolEnqueueTaskAndWaitTasks) {
  int numbers[kNumbersCount];
  for (size_t i = 0; i != kNumbersCount; ++i) numbers[i] = i;

  thread_pool_t *pool = thread_pool_init(hardware_concurrency());
  for (size_t i = 0; i != kNumbersCount; ++i)
    thread_pool_enqueue_task(pool, task, &(numbers[i]), nullptr);
  thread_pool_wait_and_destroy(pool);
  for (size_t i = 0; i != kNumbersCount; ++i) EXPECT_EQ(numbers[i], i * i);
}

void callback(void *task_res) {
  int *number = (int *)task_res;
  *number *= 2;
}

TEST(ThreadPoolEnqueueTask, ThreadPoolEnqueueTaskWithCallback) {
  int numbers[kNumbersCount];
  for (size_t i = 0; i != kNumbersCount; ++i) numbers[i] = i;

  thread_pool_t *pool = thread_pool_init(hardware_concurrency());
  for (size_t i = 0; i != kNumbersCount; ++i)
    thread_pool_enqueue_task(pool, task, &(numbers[i]), callback);
  thread_pool_wait_and_destroy(pool);
  for (size_t i = 0; i != kNumbersCount; ++i) EXPECT_EQ(numbers[i], 2 * i * i);
}

TEST(ThreadPoolEnqueueTask, ThreadPoolEnqueueToNullPool) {
  thread_pool_t *pool = nullptr;
  EXPECT_EXIT(thread_pool_enqueue_task(pool, task, nullptr, nullptr),
              ::testing::KilledBySignal(SIGABRT), "");
}

void *long_task(void *arg) {
  int *number = (int *)arg;
  *number *= 2;
  sleep(2);
  return arg;
}

TEST(ThreadPoolCancelAndDestroy, ThreadPoolCancelAndDestroy) {
  size_t hw_concurrency = hardware_concurrency();
  const size_t numbers_count = 2 * hw_concurrency;
  int *numbers = (int *)malloc(sizeof(int) * numbers_count);
  if (!numbers) FAIL() << "Internal allocation error";
  for (size_t i = 0; i != numbers_count; ++i) numbers[i] = static_cast<int>(i);

  thread_pool_t *pool = thread_pool_init(hw_concurrency);
  for (size_t i = 0; i != numbers_count; ++i)
    thread_pool_enqueue_task(pool, long_task, &numbers[i], nullptr);
  sleep(1);  // чтобы быть уверенными, что каждый поток успеет взять себе работу
  thread_pool_cancel_and_destroy(pool);

  for (size_t i = 0; i != hw_concurrency; ++i) EXPECT_EQ(numbers[i], i * 2);
  for (size_t i = hw_concurrency; i != 2 * hw_concurrency; ++i)
    EXPECT_EQ(numbers[i], i);
  free(numbers);
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

// проверим как пул заработает после паузы
TEST(ThreadPoolAwaitingWork, EnqueuePauseEnqueue) {
  size_t hw_concurrency = hardware_concurrency();
  const size_t numbers_count = 2 * hw_concurrency;
  int *numbers = (int *)malloc(sizeof(int) * numbers_count);
  if (!numbers) FAIL() << "Internal allocation error";
  for (size_t i = 0; i != numbers_count; ++i) numbers[i] = static_cast<int>(i);

  thread_pool_t *pool = thread_pool_init(hw_concurrency);
  for (size_t i = 0; i != hw_concurrency; ++i)
    thread_pool_enqueue_task(pool, task, &numbers[i], nullptr);
  sleep(1);  // чтобы быть уверенным в том что он потоки успеют отработать и
             // будут свободны
  for (size_t i = hw_concurrency; i != 2 * hw_concurrency; ++i)
    thread_pool_enqueue_task(pool, task, &numbers[i], nullptr);

  thread_pool_wait_and_destroy(pool);
  for (size_t i = 0; i != 2 * hw_concurrency; ++i) EXPECT_EQ(numbers[i], i * i);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  testing::FLAGS_gtest_death_test_style = "threadsafe";
  return RUN_ALL_TESTS();
}
