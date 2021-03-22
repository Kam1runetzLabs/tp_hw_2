//
// Created by w1ckedente on 22.03.2021.
//
#include "float_array.h"

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

struct float_array {
  float* memory;
  size_t size;
};

float_array_t* init_float_array(size_t size) {
  assert(size != 0);
  float_array_t* array = (float_array_t*)malloc(sizeof(float_array_t));
  if (!array) return NULL;

  array->memory = (float*)calloc(size, sizeof(float));
  if (!array->memory) {
    free(array);
    return NULL;
  }
  array->size = size;
  return array;
}

void free_float_array(float_array_t* array) {
  if (!array) return;
  free(array->memory);
  free(array);
}

size_t float_array_size(const float_array_t* array) {
  assert(array != NULL);
  return array->size;
}

iterator float_array_begin(const float_array_t* array) {
  assert(array != NULL);
  return array->memory;
}

iterator float_array_end(const float_array_t* array) {
  assert(array != NULL);
  return array->memory + array->size;
}

const_iterator float_array_cbegin(const float_array_t* array) {
  return float_array_begin(array);
}

const_iterator float_array_cend(const float_array_t* array) {
  return float_array_end(array);
}

float get_element(float_array_t* array, size_t index) {
  assert(array != NULL);
  assert(index < array->size);
  return array->memory[index];
}
