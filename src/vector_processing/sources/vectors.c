// Copyright 2021 Kam1runetzLabs <notsoserious2017@gmail.com>

#include <malloc.h>
#include <stddef.h>

#include "vectors.h"


vectors_3d_t *init_vectors(size_t count) {
  vectors_3d_t *vectors = (vectors_3d_t *)malloc(sizeof(vectors_3d_t));
  if (!vectors) return NULL;

  vectors->x_coords = (float *)calloc(count, sizeof(float));
  if (!vectors->x_coords) {
    free(vectors);
    return NULL;
  }

  vectors->y_coords = (float *)calloc(count, sizeof(float));
  if (!vectors->y_coords) {
    free(vectors);
    return NULL;
  }

  vectors->z_coords = (float *)calloc(count, sizeof(float));
  if (!vectors->z_coords) {
    free(vectors);
    return NULL;
  }

  vectors->count = count;

  return vectors;
}

void free_vectors(vectors_3d_t *vectors) {
  if (!vectors) return;
  free(vectors->x_coords);
  free(vectors->y_coords);
  free(vectors->z_coords);
  free(vectors);
}
