// Copyright 2021 Kam1runetzLabs <notsoserious2017@gmail.com>

#include "vectors_calc.h"

#include <stddef.h>

static float float_range_avg(const float *array, size_t size) {
  float common = 0.f;
  for (size_t i = 0; i != size; ++i) common += array[i];
  return common / (float)size;
}

int avg_coords(const vectors_3d_t *vectors, float *x_avg, float *y_avg,
               float *z_avg) {
  float *x_coords;
  float *y_coords;
  float *z_coords;

  int error = get_coords(vectors, &x_coords, &y_coords, &z_coords);
  if (error) return -1;

  size_t count = vectors_count(vectors);

  if (x_avg) *x_avg = float_range_avg(x_coords, count);
  if (y_avg) *y_avg = float_range_avg(y_coords, count);
  if (z_avg) *z_avg = float_range_avg(z_coords, count);

  return 0;
}
