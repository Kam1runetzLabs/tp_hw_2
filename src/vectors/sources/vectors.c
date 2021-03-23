// Copyright 2021 Kam1runetzLabs <notsoserious2017@gmail.com>

#include <assert.h>
#include <malloc.h>
#include <stddef.h>

#include "vectors.h"
#include "float_array.h"

#define HANDLE_BAD_ALLOC(vectors) \
  {                               \
    free_vectors(vectors);        \
    return NULL;                  \
  }

typedef struct vectors {
  float_array_t **coords;
  size_t dims;
  size_t count;
} vectors_t;

vectors_t *init_vectors(size_t capacity, size_t dims) {
  assert(capacity != 0);
  assert(dims != 0);

  vectors_t *vectors = (vectors_t *)malloc(sizeof(vectors_t));
  if (!vectors) HANDLE_BAD_ALLOC(vectors);

  vectors->coords = (float_array_t **)calloc(dims, sizeof(float_array_t *));
  if (!vectors->coords) HANDLE_BAD_ALLOC(vectors);

  vectors->dims = dims;
  vectors->count = 0;

  for (size_t i = 0; i != dims; ++i) {
    vectors->coords[i] = init_float_array(capacity);
    if (!vectors->coords[i]) HANDLE_BAD_ALLOC(vectors);
  }

  return vectors;
}

void add_vector(vectors_t *vectors, const float_array_t *vectors_coords) {
  assert(vectors != NULL);
  assert(vectors->count != vectors_capacity(vectors));
  assert(vectors_coords != NULL);
  assert(float_array_size(vectors_coords) == vectors->dims);

  for (size_t i = 0; i != vectors->dims; ++i) {
    float coord = float_array_get_element(vectors_coords, i);
    float_array_set_element(vectors->coords[i], vectors->count, coord);
  }

  vectors->count++;
}

float_array_t *get_coords(const vectors_t *vectors, size_t dim) {
  assert(vectors != NULL);
  assert(dim < vectors->dims);
  return vectors->coords[dim];
}

size_t vectors_count(const vectors_t *vectors) {
  assert(vectors != NULL);
  return vectors->count;
}

size_t vectors_capacity(const vectors_t *vectors) {
  assert(vectors != NULL);
  return float_array_size(vectors->coords[0]);
}

void free_vectors(vectors_t *vectors) {
  if (!vectors) return;
  if (vectors->coords)
    for (size_t i = 0; i != vectors->dims; ++i)
      free_float_array(vectors->coords[i]);
  free(vectors->coords);
  free(vectors);
}
