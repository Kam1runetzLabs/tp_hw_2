// Copyright 2021 Kam1runetzLabs <notsoserious2017@gmail.com>

#include <assert.h>
#include <stddef.h>
#include <stdio.h>

#include "utility.h"

size_t fill_vectors(FILE *file, vectors_3d_t *vectors) {
  assert(file != NULL);
  assert(vectors != NULL);

  float x = 0.f;
  float y = 0.f;
  float z = 0.f;

  size_t read_count = 0;

  size_t capacity = vectors_capacity(vectors);
  for (; read_count != capacity && !feof(file); ++read_count) {
    if (fscanf(file, "%f%f%f", &x, &y, &z) != 3) return read_count - 1;
    add_vector(vectors, x, y, z);
  }

  return read_count;
}
