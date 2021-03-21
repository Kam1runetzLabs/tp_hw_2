// Copyright 2021 Kam1runetzLabs <notsoserious2017@gmail.com>

#include <stddef.h>

#include "vectors_calc.h"

static inline float range_avg(const float *array, size_t size) {
  float common = 0.f;
  for (size_t i = 0; i != size; ++i) common += array[i];
  return common / (float)size;
}

int avg_coords(const vectors_3d_t *vectors, float *x_avg, float *y_avg,
               float *z_avg) {
  if (!vectors) return -1;

  if (x_avg) *x_avg = range_avg(vectors->x_coords, vectors->count);
  if (y_avg) *y_avg = range_avg(vectors->y_coords, vectors->count);
  if (z_avg) *z_avg = range_avg(vectors->z_coords, vectors->count);

  return 0;
}
