// Copyright 2021 Kam1runetzLabs <notsoserious2017@gmail.com>

#include <assert.h>
#include <stddef.h>
#include <stdio.h>

#include "utility.h"
#include "float_array.h"

size_t fill_vectors(FILE *file, vectors_t *vectors) {
  assert(file != NULL && vectors != NULL);

  size_t read_count = 0;
  float_array_t *vector = float_array_init(vectors_dims(vectors));
  if (!vector) return 0;

  size_t capacity = vectors_capacity(vectors);
  size_t dims = vectors_dims(vectors);
  for (; read_count != capacity && !feof(file); ++read_count) {
    for (size_t i = 0; i != dims; ++i) {
      float buf;
      if (fscanf(file, "%f", &buf) != 1) {
        float_array_free(vector);
        return read_count;
      }
      float_array_set_element(vector, i, buf);
    }
    add_vector(vectors, vector);
  }

  return read_count;
}
