// Copyright 2021 Kam1runetzLabs <notsoserious2017@gmail.com>

#ifndef VECTOR_PROCESSING_INCLUDE_VECTORS_H_
#define VECTOR_PROCESSING_INCLUDE_VECTORS_H_

#include <stddef.h>

typedef struct vectors_3d vectors_3d_t;

///@todo documentation
vectors_3d_t *init_vectors(size_t count);

int add_vector(vectors_3d_t *vectors, float x, float y, float z);

int get_coords(const vectors_3d_t *vectors, float **x_range, float **y_range,
               float **z_range);

size_t vectors_count(const vectors_3d_t *vectors);

size_t vectors_capacity(const vectors_3d_t *vectors);

///@todo documentation
void free_vectors(vectors_3d_t *vectors);

#endif  // VECTOR_PROCESSING_INCLUDE_VECTORS_H_
