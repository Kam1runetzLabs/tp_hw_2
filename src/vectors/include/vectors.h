// Copyright 2021 Kam1runetzLabs <notsoserious2017@gmail.com>

#ifndef _3D_VECTORS_INCLUDE_VECTORS_H_
#define _3D_VECTORS_INCLUDE_VECTORS_H_

#include <stddef.h>

#include "float_array.h"

typedef struct vectors vectors_t;

vectors_t *vectors_init(size_t capacity, size_t dims);

void add_vector(vectors_t *vectors, const float_array_t *vectors_coords);

float_array_t *get_coords(const vectors_t *vectors, size_t dim);

size_t vectors_count(const vectors_t *vectors);

size_t vectors_capacity(const vectors_t *vectors);

size_t vectors_dims(const vectors_t *vectors);

void vectors_free(vectors_t *vectors);

#endif  // _3D_VECTORS_INCLUDE_VECTORS_H_
