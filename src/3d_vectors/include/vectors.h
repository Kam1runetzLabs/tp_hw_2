// Copyright 2021 Kam1runetzLabs <notsoserious2017@gmail.com>

#ifndef _3D_VECTORS_INCLUDE_VECTORS_H_
#define _3D_VECTORS_INCLUDE_VECTORS_H_

#include <stddef.h>

#include "float_array.h"

typedef struct vectors_3d vectors_3d_t;

vectors_3d_t *init_vectors(size_t capacity);

void add_vector(vectors_3d_t *vectors, float x, float y, float z);

void get_coords(const vectors_3d_t *vectors, float_array_t **x_coords,
                float_array_t **y_coords, float_array_t **z_coords);

void get_vector(const vectors_3d_t *vectors, size_t ind, float *x, float *y,
                float *z);

size_t vectors_count(const vectors_3d_t *vectors);

size_t vectors_capacity(const vectors_3d_t *vectors);

void free_vectors(vectors_3d_t *vectors);

#endif  // _3D_VECTORS_INCLUDE_VECTORS_H_
