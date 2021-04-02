// Copyright 2021 Kam1runetzLabs <notsoserious2017@gmail.com>

#include "float_array.h"

#include <stddef.h>
#include <stdlib.h>

struct float_array {
  float *memory;
  size_t size;
};

float_array_t *float_array_init(size_t size) {
  if (!size) return NULL;
  float_array_t *array = (float_array_t *)malloc(sizeof(float_array_t));
  if (!array) return NULL;

  array->memory = (float *)calloc(size, sizeof(float));
  if (!array->memory) {
    free(array);
    return NULL;
  }
  array->size = size;
  return array;
}

void float_array_free(float_array_t *array) {
  if (!array) return;
  free(array->memory);
  free(array);
}

size_t float_array_size(const float_array_t *array) {
  if (!array) return 0;
  return array->size;
}

iterator float_array_begin(const float_array_t *array) {
  if (!array) return NULL;
  return array->memory;
}

iterator float_array_end(const float_array_t *array) {
  if (!array) return NULL;
  return array->memory + array->size;
}

const_iterator float_array_cbegin(const float_array_t *array) {
  return float_array_begin(array);
}

const_iterator float_array_cend(const float_array_t *array) {
  return float_array_end(array);
}

int float_array_get_element(const float_array_t *array, size_t index,
                            float *element) {
  if (!array || !element) return -1;
  if (index >= array->size) return -1;
  *element = array->memory[index];
  return 0;
}

int float_array_set_element(float_array_t *array, size_t index, float value) {
  if (!array || index >= array->size) return -1;
  array->memory[index] = value;
  return 0;
}
