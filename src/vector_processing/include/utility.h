// Copyright 2021 Kam1runetzLabs <notsoserious2017@gmail.com>

#ifndef VECTOR_PROCESSING_INCLUDE_UTILITY_H_
#define VECTOR_PROCESSING_INCLUDE_UTILITY_H_

#include <stddef.h>
#include <stdio.h>

#include "vectors.h"

typedef enum {
  ERR_SUCCESS               =  0,
  ERR_UNINITIALIZED_FILE    = -1,
  ERR_UNINITIALIZED_VECTORS = -2,
  ERR_FILE_READING_FAILED   = -3,
} err_code_t;

///@todo documentation
///@param vectors must be initialized
err_code_t fill_vectors(FILE *file, vectors_3d_t *vectors);

#endif  // VECTOR_PROCESSING_INCLUDE_UTILITY_H_
