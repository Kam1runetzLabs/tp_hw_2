// Copyright 2021 Kam1runetzLabs <notsoserious2017@gmail.com>

#include "utility.h"

#include <stddef.h>
#include <stdio.h>

int fill_vectors(FILE *file, vectors_3d_t *vectors, size_t *read_count_ptr) {
  if (read_count_ptr) *read_count_ptr = 0;

  if (!file) return -1;
  if (!vectors) return -1;

  float x = 0.f;
  float y = 0.f;
  float z = 0.f;

  size_t read_count = 0;

  size_t capacity = vectors_capacity(vectors);
  for (; read_count != capacity && !feof(file); ++read_count) {
    if (fscanf(file, "%f%f%f", &x, &y, &z) != 3) return -1;
    int error = add_vector(vectors, x, y, z);
    if (error) return -1;
  }

  if (read_count_ptr) *read_count_ptr = read_count;
  return 0;
}
