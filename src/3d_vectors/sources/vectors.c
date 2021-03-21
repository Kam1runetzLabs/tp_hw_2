// Copyright 2021 Kam1runetzLabs <notsoserious2017@gmail.com>

#include "vectors.h"

#include <malloc.h>
#include <stddef.h>

typedef struct vectors_3d {
  float *x_coords;
  float *y_coords;
  float *z_coords;
  size_t count;
  size_t capacity;
} vectors_3d_t;

vectors_3d_t *init_vectors(size_t capacity) {
  vectors_3d_t *vectors = (vectors_3d_t *)malloc(sizeof(vectors_3d_t));
  if (!vectors) return NULL;

  vectors->x_coords = (float *)calloc(capacity, sizeof(float));
  if (!vectors->x_coords) {
    free(vectors);
    return NULL;
  }

  vectors->y_coords = (float *)calloc(capacity, sizeof(float));
  if (!vectors->y_coords) {
    free(vectors);
    return NULL;
  }

  vectors->z_coords = (float *)calloc(capacity, sizeof(float));
  if (!vectors->z_coords) {
    free(vectors);
    return NULL;
  }

  vectors->capacity = capacity;
  vectors->count = 0;

  return vectors;
}

int add_vector(vectors_3d_t *vectors, float x, float y, float z) {
  if (!vectors) return -1;
  if (!vectors->x_coords || !vectors->y_coords || !vectors->z_coords) return -1;
  if (vectors->count == vectors->capacity) return -1;

  vectors->x_coords[vectors->count] = x;
  vectors->y_coords[vectors->count] = y;
  vectors->z_coords[vectors->count] = z;
  vectors->count++;
  return 0;
}

int get_coords(const vectors_3d_t *vectors, float **x_range, float **y_range,
               float **z_range) {
  if (!vectors) return -1;
  if (!vectors->x_coords || !vectors->y_coords || !vectors->z_coords) return -1;

  if (x_range) *x_range = vectors->x_coords;
  if (y_range) *y_range = vectors->y_coords;
  if (z_range) *z_range = vectors->z_coords;

  return 0;
}

size_t vectors_count(const vectors_3d_t *vectors) {
  if (!vectors) return 0;
  return vectors->count;
}

size_t vectors_capacity(const vectors_3d_t *vectors) {
  if (!vectors) return 0;
  return vectors->capacity;
}

void free_vectors(vectors_3d_t *vectors) {
  if (!vectors) return;
  free(vectors->x_coords);
  free(vectors->y_coords);
  free(vectors->z_coords);
  free(vectors);
}
