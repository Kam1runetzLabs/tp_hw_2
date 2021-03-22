// Copyright 2021 Kam1runetzLabs <notsoserious2017@gmail.com>

#include <assert.h>
#include <stddef.h>

#include "vectors_calc.h"
#include "float_array.h"

static float float_range_avg(const float_array_t *array, size_t size) {
  float common = 0.f;
  for (size_t i = 0; i != size; ++i)
    common += float_array_get_element(array, i);
  return common / (float)size;
}

void avg_coords(const vectors_3d_t *vectors, float *x_avg, float *y_avg,
                float *z_avg) {
  assert(vectors != NULL);
  float_array_t *x_coords;
  float_array_t *y_coords;
  float_array_t *z_coords;

  get_coords(vectors, &x_coords, &y_coords, &z_coords);

  size_t count = vectors_count(vectors);

  if (x_avg) *x_avg = float_range_avg(x_coords, count);
  if (y_avg) *y_avg = float_range_avg(y_coords, count);
  if (z_avg) *z_avg = float_range_avg(z_coords, count);
}
