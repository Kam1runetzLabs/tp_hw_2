// Copyright 2021 Kam1runetzLabs <notsoserious2017@gmail.com>

#include "vectors.h"

#include <assert.h>
#include <malloc.h>
#include <stddef.h>
#include <stdio.h>

#include "float_array.h"
#include "vectors.h"

typedef struct vectors {
  float_array_t **coords;
  size_t dims;
  size_t count;
} vectors_t;

vectors_t *vectors_init(size_t capacity, size_t dims) {
  assert(capacity != 0 && dims != 0);

  vectors_t *vectors = (vectors_t *)malloc(sizeof(vectors_t));
  if (!vectors) return NULL;

  vectors->coords = (float_array_t **)calloc(dims, sizeof(float_array_t *));
  if (!vectors->coords) {
    vectors_free(vectors);
    return NULL;
  }

  vectors->dims = dims;
  vectors->count = 0;

  for (size_t i = 0; i != dims; ++i) {
    vectors->coords[i] = float_array_init(capacity);
    if (!vectors->coords[i]) {
      vectors_free(vectors);
      return NULL;
    }
  }

  return vectors;
}

int vectors_fill(FILE *file, vectors_t *vectors) {
  assert(file != NULL && vectors != NULL);
  size_t dims = vectors_dims(vectors);

  for (size_t i = 0; i != dims; ++i) {
    iterator begin = float_array_begin(vectors->coords[i]);
    iterator end = float_array_end(vectors->coords[i]);
    for (iterator it = begin; it != end; ++it) {
      float buf;
      if (fscanf(file, "%f", &buf) != 1) {
        vectors->count = 0;
        return -1;
      }
      *it = buf;
      vectors->count++;
    }
  }
  return 0;
}

void vectors_add_vector(vectors_t *vectors,
                        const float_array_t *vectors_coords) {
  assert(vectors != NULL && vectors_coords != NULL);
  assert(vectors->count < vectors_capacity(vectors));
  assert(float_array_size(vectors_coords) == vectors->dims);

  for (size_t i = 0; i != vectors->dims; ++i) {
    float coord = float_array_get_element(vectors_coords, i);
    float_array_set_element(vectors->coords[i], vectors->count, coord);
  }
  vectors->count++;
}

float_array_t *vectors_get_coords(const vectors_t *vectors, size_t dim) {
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

size_t vectors_dims(const vectors_t *vectors) {
  assert(vectors != NULL);
  return vectors->dims;
}

void vectors_free(vectors_t *vectors) {
  if (!vectors) return;
  if (vectors->coords) {
    for (size_t i = 0; i != vectors->dims; ++i)
      float_array_free(vectors->coords[i]);
  }

  free(vectors->coords);
  free(vectors);
}
