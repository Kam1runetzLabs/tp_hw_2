// Copyright 2021 Kam1runetzLabs <notsoserious2017@gmail.com>

#ifndef VECTOR_PROCESSING_INCLUDE_VECTORS_H_
#define VECTOR_PROCESSING_INCLUDE_VECTORS_H_

#include <stddef.h>

typedef struct {
  float *x_coords;
  float *y_coords;
  float *z_coords;
  size_t count;
} vectors_3d_t;

///@todo documentation
vectors_3d_t *init_vectors(size_t count);

///@todo documentation
void free_vectors(vectors_3d_t *vectors);

#endif  // VECTOR_PROCESSING_INCLUDE_VECTORS_H_
