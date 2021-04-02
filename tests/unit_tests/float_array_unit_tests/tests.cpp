// Copyright 2021 Kam1runetzLabs <notsoserious2017@gmail.com>

#include <gtest/gtest.h>

#include <ctime>

extern "C" {
#include "float_array.h"
}

const size_t array_size = 123;
const size_t invalid_array_size = -1;

TEST(FloatArrayInit, ValidInitFloatArray) {
  float_array_t *array = float_array_init(array_size);
  EXPECT_TRUE(array);
  for (size_t i = 0; i != array_size; ++i) {
    float element;
    float_array_get_element(array, i, &element);
    EXPECT_FLOAT_EQ(0.f, element);
  }
  float_array_free(array);
}

TEST(FloatArrayInit, InitWithInvalidSize) {
  float_array_t *array = float_array_init(invalid_array_size);
  EXPECT_FALSE(array);
}

TEST(FloatArrayInit, InitWithNullSize) {
  float_array_t *array;
  array = float_array_init(0);
  EXPECT_FALSE(array);
}

TEST(FloatArraySizeGetter, GettingArraySize) {
  float_array_t *array = float_array_init(array_size);
  EXPECT_EQ(float_array_size(array), array_size);
  float_array_free(array);
}

TEST(FloatArraySizeGetter, GettingNullArraySize) {
  float_array_t *array = nullptr;
  size_t size = float_array_size(array);
  EXPECT_EQ(size, 0);
}

TEST(FloatArrayIterators, BeginIterator) {
  float_array_t *array = float_array_init(array_size);
  static unsigned int seed = time(nullptr);
  for (size_t i = 0; i != array_size; ++i)
    float_array_set_element(array, i, static_cast<float>(rand_r(&seed)));
  iterator begin = float_array_begin(array);
  EXPECT_TRUE(begin);
  float element;
  float_array_get_element(array, 0, &element);
  EXPECT_FLOAT_EQ(*begin, element);
  float_array_free(array);
}

TEST(FloatArrayIterators, BeginIteratorFromNullArray) {
  float_array_t *array = nullptr;
  iterator begin = float_array_begin(array);
  EXPECT_FALSE(begin);
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
  float_array_t *array = nullptr;
  iterator end = float_array_end(array);
  EXPECT_FALSE(end);
}

TEST(FloatArrayIterators, AssignValueByIterator) {
  static unsigned int seed = time(nullptr);
  float_array_t *array = float_array_init(array_size);
  iterator begin = float_array_begin(array);
  const size_t index = rand_r(&seed) % array_size;
  float element;
  float_array_get_element(array, index, &element);
  EXPECT_FLOAT_EQ(element, 0.f);

  const float value = 12.34;
  *(begin + index) = value;
  float_array_get_element(array, index, &element);
  EXPECT_FLOAT_EQ(element, value);
  float_array_free(array);
}

TEST(FloatArrayConstIterators, CBeginIterator) {
  static unsigned int seed = time(nullptr);
  float_array_t *array = float_array_init(array_size);
  for (size_t i = 0; i != array_size; ++i)
    float_array_set_element(array, i, static_cast<float>(rand_r(&seed)));
  const_iterator begin = float_array_cbegin(array);
  EXPECT_TRUE(begin);
  float element;
  float_array_get_element(array, 0, &element);
  EXPECT_FLOAT_EQ(*begin, element);
  float_array_free(array);
}

TEST(FloatArrayConstIterators, CBeginIteratorFromNullArray) {
  float_array_t *array = nullptr;
  const_iterator begin = float_array_cbegin(array);
  EXPECT_FALSE(begin);
}

TEST(FloatArrayConstIterators, CEndIterator) {
  float_array_t *array = float_array_init(array_size);
  const_iterator end = float_array_cend(array);
  const_iterator begin = float_array_cbegin(array);
  size_t arr_size = float_array_size(array);

  EXPECT_EQ(begin + arr_size, end);
  float_array_free(array);
}

TEST(FloatArrayConstIterators, CEndIteratorFromNullArray) {
  float_array_t *array = nullptr;
  const_iterator end = float_array_cend(array);
  EXPECT_FALSE(end);
}

TEST(FloatArrayGetElement, GettingElement) {
  static unsigned int seed = time(nullptr);
  float_array_t *array = float_array_init(array_size);
  iterator it = float_array_begin(array);
  const size_t index = rand_r(&seed) % array_size;
  const float value = 12.34;
  *(it + index) = value;
  float element;
  float_array_get_element(array, index, &element);
  EXPECT_FLOAT_EQ(element, value);
  float_array_free(array);
}

TEST(FloatArrayGetElement, GettingElementFromNullArray) {
  const size_t index = 1;
  float_array_t *array = nullptr;
  float element;
  int error = float_array_get_element(array, index, &element);
  EXPECT_TRUE(error);
}

TEST(FloatArrayGetElement, GettingElementFromOverRangeArray) {
  float_array_t *array = float_array_init(array_size);
  float element;
  int error = float_array_get_element(array, array_size, &element);
  EXPECT_TRUE(error);
  float_array_free(array);
}

TEST(FloatArrayGetElement, GettingElementToNullValuePtr) {
  float_array_t *array = float_array_init(array_size);
  int error = float_array_get_element(array, array_size, NULL);
  EXPECT_TRUE(error);
  float_array_free(array);
}

TEST(FloatArraySetElement, SettingElement) {
  static unsigned int seed = time(nullptr);
  float_array_t *array = float_array_init(array_size);
  const size_t index = rand_r(&seed) % array_size;
  const float value = 12.34;
  float_array_set_element(array, index, value);
  float element;
  float_array_get_element(array, index, &element);
  EXPECT_FLOAT_EQ(element, value);
  float_array_free(array);
}

TEST(FloatArraySetElement, SettingElementToNullArray) {
  const size_t index = 1;
  const float value = 12.34;
  float_array_t *array = nullptr;
  int error = float_array_set_element(array, index, value);
  EXPECT_TRUE(error);
}

TEST(FloatArraySetElement, SettingElementToOverRangeArray) {
  float_array_t *array = float_array_init(array_size);
  const float value = 12.34;
  int error = float_array_set_element(array, array_size, value);
  EXPECT_TRUE(error);
  float_array_free(array);
}
