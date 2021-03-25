// Copyright 2021 Kam1runetzLabs <notsoserious2017@gmail.com>

#ifndef FLOAT_ARRAY_INCLUDE_FLOAT_ARRAY_H_
#define FLOAT_ARRAY_INCLUDE_FLOAT_ARRAY_H_

#include <stddef.h>

typedef struct float_array float_array_t;
typedef float *iterator;
typedef const float *const_iterator;

float_array_t *float_array_init(size_t size);

void float_array_free(float_array_t *array);

size_t float_array_size(const float_array_t *array);

iterator float_array_begin(const float_array_t *array);

iterator float_array_end(const float_array_t *array);

const_iterator float_array_cbegin(const float_array_t *array);

const_iterator float_array_cend(const float_array_t *array);

float float_array_get_element(const float_array_t *array, size_t index);

void float_array_set_element(float_array_t *array, size_t index, float value);

#endif  // FLOAT_ARRAY_INCLUDE_FLOAT_ARRAY_H_
