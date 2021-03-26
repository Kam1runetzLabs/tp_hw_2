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

TEST(FloatArraySizeGetter, GettingArraySize) {
  float_array_t *array = float_array_init(array_size);
  EXPECT_EQ(float_array_size(array), array_size);
  float_array_free(array);
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

TEST(FloatArrayIterators, EndIterator) {
  float_array_t *array = float_array_init(array_size);
  iterator end = float_array_end(array);
  iterator begin = float_array_begin(array);
  size_t arr_size = float_array_size(array);

  EXPECT_EQ(begin + arr_size, end);
  float_array_free(array);
}

TEST(FloatArrayIterators, AssignValueByIterator) {
  float_array_t *array = float_array_init(array_size);
  iterator begin = float_array_begin(array);
  const size_t index = 3;
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

TEST(FloatArrayConstIterators, CEndIterator) {
  float_array_t *array = float_array_init(array_size);
  const_iterator end = float_array_cend(array);
  const_iterator begin = float_array_cbegin(array);
  size_t arr_size = float_array_size(array);

  EXPECT_EQ(begin + arr_size, end);
  float_array_free(array);
}
