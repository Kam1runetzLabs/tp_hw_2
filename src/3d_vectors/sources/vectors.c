// Copyright 2021 Kam1runetzLabs <notsoserious2017@gmail.com>

#include <assert.h>
#include <malloc.h>
#include <stddef.h>

#include "vectors.h"
#include "float_array.h"

#define BAD_ALLOC_HANDLE(vectors, x_coords, y_coords, z_coords) \
  {                                                             \
    free(x_coords);                                             \
    free(y_coords);                                             \
    free(z_coords);                                             \
    free(vectors);                                              \
    return NULL;                                                \
  }

typedef struct vectors_3d {
  float_array_t *x_coords;
  float_array_t *y_coords;
  float_array_t *z_coords;
  size_t count;
} vectors_3d_t;

vectors_3d_t *init_vectors(size_t capacity) {
  assert(capacity != 0);
  vectors_3d_t *vectors = (vectors_3d_t *)malloc(sizeof(vectors_3d_t));
  if (!vectors) BAD_ALLOC_HANDLE(vectors, NULL, NULL, NULL);

  vectors->x_coords = init_float_array(capacity);
  if (!vectors->x_coords) BAD_ALLOC_HANDLE(vectors, NULL, NULL, NULL);

  vectors->y_coords = init_float_array(capacity);
  if (!vectors->y_coords)
    BAD_ALLOC_HANDLE(vectors, vectors->x_coords, NULL, NULL);

  vectors->z_coords = init_float_array(capacity);
  if (!vectors->z_coords)
    BAD_ALLOC_HANDLE(vectors, vectors->x_coords, vectors->y_coords, NULL);

  vectors->count = 0;

  return vectors;
}

void add_vector(vectors_3d_t *vectors, float x, float y, float z) {
  assert(vectors != NULL);
  assert(vectors->count != vectors_capacity(vectors));

  float_array_set_element(vectors->x_coords, vectors->count, x);
  float_array_set_element(vectors->y_coords, vectors->count, y);
  float_array_set_element(vectors->z_coords, vectors->count, z);

  vectors->count++;
}

void get_coords(const vectors_3d_t *vectors, float_array_t **x_coords,
                float_array_t **y_coords, float_array_t **z_coords) {
  assert(vectors != NULL);
  if (x_coords) *x_coords = vectors->x_coords;
  if (y_coords) *y_coords = vectors->y_coords;
  if (z_coords) *z_coords = vectors->z_coords;
}

void get_vector(const vectors_3d_t *vectors, size_t ind, float *x, float *y,
                float *z) {
  assert(vectors != NULL);
  assert(ind < vectors->count);

  if (x) *x = float_array_get_element(vectors->x_coords, ind);
  if (y) *y = float_array_get_element(vectors->y_coords, ind);
  if (z) *z = float_array_get_element(vectors->z_coords, ind);
}

size_t vectors_count(const vectors_3d_t *vectors) {
  assert(vectors != NULL);
  return vectors->count;
}

size_t vectors_capacity(const vectors_3d_t *vectors) {
  assert(vectors != NULL);
  return float_array_size(vectors->x_coords);
}

void free_vectors(vectors_3d_t *vectors) {
  if (!vectors) return;
  free_float_array(vectors->x_coords);
  free_float_array(vectors->y_coords);
  free_float_array(vectors->z_coords);
  free(vectors);
}
