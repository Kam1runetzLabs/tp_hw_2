// Copyright 2021 Kam1runetzLabs <notsoserious2017@gmail.com>

#include <stddef.h>
#include <stdio.h>

#include "utility.h"

// todo refactor this
// todo return read vectors count
err_code_t fill_vectors(FILE *file, vectors_3d_t *vectors) {
  if (!file) return ERR_UNINITIALIZED_FILE;
  if (!vectors) return ERR_UNINITIALIZED_VECTORS;

  float cur_x = 0.f;
  float cur_y = 0.f;
  float cur_z = 0.f;

  for (size_t i = 0; i < vectors->count && !feof(file); ++i) {
    if (fscanf(file, "%f%f%f", &cur_x, &cur_y, &cur_z) != 3)
      return ERR_FILE_READING_FAILED;
    vectors->x_coords[i] = cur_x;
    vectors->y_coords[i] = cur_y;
    vectors->z_coords[i] = cur_z;
  }

  return ERR_SUCCESS;
}
