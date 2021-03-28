// Copyright 2021 Kam1runetzLabs <notsoserious2017@gmail.com>

#include <gtest/gtest.h>

extern "C" {
#include "float_array.h"
}

const size_t array_size = 1234;
const size_t invalid_array_size = -1;

TEST(FloatArrayInit, ValidInitFloatArray) {
  float_array_t *array = float_array_init(array_size);
  EXPECT_TRUE(array);
  for (size_t i = 0; i != array_size; ++i)
    EXPECT_FLOAT_EQ(0.f, float_array_get_element(array, i));
  float_array_free(array);
}

TEST(FloatArrayInit, InitWithInvalidSize) {
  float_array_t *array = float_array_init(invalid_array_size);
  EXPECT_FALSE(array);
}

TEST(FloatArrayInit, InitWithNullSize) {
  float_array_t *array = NULL;
  EXPECT_EXIT(array = float_array_init(0), ::testing::KilledBySignal(SIGABRT),
              "");
  EXPECT_FALSE(array);
}

TEST(FloatArraySizeGetter, GettingArraySize) {
  float_array_t *array = float_array_init(array_size);
  EXPECT_EQ(float_array_size(array), array_size);
  float_array_free(array);
}

TEST(FloatArraySizeGetter, GettingNullArraySize) {
  EXPECT_EXIT(float_array_size(NULL), ::testing::KilledBySignal(SIGABRT), "");
}

TEST(FloatArrayIterators, BeginIterator) {
  float_array_t *array = float_array_init(array_size);
  for (size_t i = 0; i != array_size; ++i)
    float_array_set_element(array, i, static_cast<float>(rand()));
  iterator begin = float_array_begin(array);
  EXPECT_TRUE(begin);
  EXPECT_EQ(*begin, float_array_get_element(array, 0));
  float_array_free(array);
}

TEST(FloatArrayIterators, BeginIteratorFromNullArray) {
  EXPECT_EXIT(float_array_begin(NULL), ::testing::KilledBySignal(SIGABRT), "");
}

TEST(FloatArrayIterators, EndIterator) {
  float_array_t *array = float_array_init(array_size);
  iterator end = float_array_end(array);
  iterator begin = float_array_begin(array);
  size_t arr_size = float_array_size(array);

  EXPECT_EQ(begin + arr_size, end);
  float_array_free(array);
}

TEST(FloatArrayIterators, EndIteratorFromNullArray) {
  EXPECT_EXIT(float_array_end(NULL), ::testing::KilledBySignal(SIGABRT), "");
}

TEST(FloatArrayIterators, AssignValueByIterator) {
  float_array_t *array = float_array_init(array_size);
  iterator begin = float_array_begin(array);
  const size_t index = rand() % array_size;
  EXPECT_FLOAT_EQ(float_array_get_element(array, index), 0.f);

  const float value = 12.34;
  *(begin + index) = value;
  EXPECT_FLOAT_EQ(float_array_get_element(array, index), value);
}

TEST(FloatArrayConstIterators, CBeginIterator) {
  float_array_t *array = float_array_init(array_size);
  for (size_t i = 0; i != array_size; ++i)
    float_array_set_element(array, i, static_cast<float>(rand()));
  const_iterator begin = float_array_cbegin(array);
  EXPECT_TRUE(begin);
  EXPECT_EQ(*begin, float_array_get_element(array, 0));
  float_array_free(array);
}

TEST(FloatArrayIterators, CBeginIterator) {
  EXPECT_EXIT(float_array_cbegin(NULL), ::testing::KilledBySignal(SIGABRT), "");
}

TEST(FloatArrayConstIterators, CEndIterator) {
  float_array_t *array = float_array_init(array_size);
  const_iterator end = float_array_cend(array);
  const_iterator begin = float_array_cbegin(array);
  size_t arr_size = float_array_size(array);

  EXPECT_EQ(begin + arr_size, end);
  float_array_free(array);
}

TEST(FloatArrayIterators, CEndIteratorFromNullArray) {
  EXPECT_EXIT(float_array_cend(NULL), ::testing::KilledBySignal(SIGABRT), "");
}

TEST(FloatArrayGetElement, GettingElement) {
  float_array_t *array = float_array_init(array_size);
  iterator it = float_array_begin(array);
  const size_t index = rand() % array_size;
  const float value = 12.34;
  *(it + index) = value;
  EXPECT_FLOAT_EQ(float_array_get_element(array, index), value);
  float_array_free(array);
}

TEST(FloatArrayGetElement, GettingElementFromNullArray) {
  const size_t index = 1;
  EXPECT_EXIT(float_array_get_element(NULL, index),
              ::testing::KilledBySignal(SIGABRT), "");
}

TEST(FloatArrayGetElement, GettingElementFromOverRangeArray) {
  float_array_t *array = float_array_init(array_size);
  EXPECT_EXIT(float_array_get_element(array, array_size),
              ::testing::KilledBySignal(SIGABRT), "");
  float_array_free(array);
}

TEST(FloatArraySetElement, SettingElement) {
  float_array_t *array = float_array_init(array_size);
  const size_t index = rand() % array_size;
  const float value = 12.34;
  float_array_set_element(array, index, value);
  EXPECT_FLOAT_EQ(float_array_get_element(array, index), value);
  float_array_free(array);
}

TEST(FloatArraySetElement, SettingElementToNullArray) {
  const size_t index = 1;
  const float value = 12.34;
  EXPECT_EXIT(float_array_set_element(NULL, index, value),
              ::testing::KilledBySignal(SIGABRT), "");
}

TEST(FloatArraySetElement, SettingElementToOverRangeArray) {
  float_array_t *array = float_array_init(array_size);
  const float value = 12.34;
  EXPECT_EXIT(float_array_set_element(array, array_size, value),
              ::testing::KilledBySignal(SIGABRT), "");
  float_array_free(array);
}
