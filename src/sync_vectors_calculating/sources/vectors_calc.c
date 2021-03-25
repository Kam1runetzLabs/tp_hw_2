// Copyright 2021 Kam1runetzLabs <notsoserious2017@gmail.com>

#include "vectors_calc.h"

#include <assert.h>
#include <stddef.h>

#include "float_array.h"

static float float_range_avg(const float_array_t *array, size_t size) {
  float common = 0.f;
  for (size_t i = 0; i != size; ++i)
    common += float_array_get_element(array, i);
  return common / (float)size;
}

float_array_t *calc_avg_vector(const vectors_t *vectors) {
  assert(vectors != NULL);
  float_array_t *avg_vector = float_array_init(vectors_dims(vectors));
  if (!avg_vector) return NULL;

  size_t dims = vectors_dims(vectors);
  for (size_t i = 0; i != dims; ++i) {
    float buf =
        float_range_avg(vectors_get_coords(vectors, i), vectors_count(vectors));
    float_array_set_element(avg_vector, i, buf);
  }
  return avg_vector;
}
