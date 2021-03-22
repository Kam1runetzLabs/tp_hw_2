//
// Created by w1ckedente on 22.03.2021.
//

#ifndef TEMPLATE_FLOAT_ARRAY_H
#define TEMPLATE_FLOAT_ARRAY_H

#include <stddef.h>

typedef struct float_array float_array_t;
typedef float *iterator;
typedef const float *const_iterator;

float_array_t *init_float_array(size_t size);

void free_float_array(float_array_t *array);

size_t float_array_size(const float_array_t *array);

iterator float_array_begin(const float_array_t *array);

iterator float_array_end(const float_array_t *array);

const_iterator float_array_cbegin(const float_array_t *array);

const_iterator float_array_cend(const float_array_t *array);

float get_element(const float_array_t *array, size_t index);

void set_element(float_array_t *array, size_t index, float value);

#endif  // TEMPLATE_FLOAT_ARRAY_H
