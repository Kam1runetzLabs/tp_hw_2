// Copyright 2021 Kam1runetzLabs <notsoserious2017@gmail.com>

#include <gtest/gtest.h>

extern "C" {
#include "float_array.h"
#include "vectors.h"
#include "vectors_calc.h"
}

const size_t dims = 3;
const size_t capacity = 123;

static float calc_avg_range(const float_array_t *range) {
  float common = 0.f;
  for (const_iterator it = float_array_cbegin(range);
       it != float_array_cend(range); ++it)
    common += *it;
  return common / static_cast<float>(float_array_size(range));
}

TEST(CalcAvgVectors, CalcAvgVectors) {
  vectors_t *vectors = vectors_init(capacity, dims);
  for (size_t i = 0; i != capacity; ++i) {
    float_array_t *new_vector = float_array_init(dims);
    for (size_t j = 0; j != dims; ++j) {
      float_array_set_element(new_vector, j, static_cast<float>(j));
    }
    vectors_add_vector(vectors, new_vector);
    float_array_free(new_vector);
  }
  float_array_t *avg_vector = calc_avg_vector(vectors);
  for (size_t i = 0; i != dims; ++i) {
    float_array_t *coords_range = vectors_get_coords(vectors, i);
    float coord;
    float_array_get_element(avg_vector, i, &coord);
    EXPECT_FLOAT_EQ(calc_avg_range(coords_range), coord);
  }
  float_array_free(avg_vector);
  vectors_free(vectors);
}

TEST(CalcAvgVectors, CalcFromNullVectors) {
  vectors_t *vectors = nullptr;
  float_array_t *avg_vector = calc_avg_vector(vectors);
  EXPECT_FALSE(avg_vector);
}
