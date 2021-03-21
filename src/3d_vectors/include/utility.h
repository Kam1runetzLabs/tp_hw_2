// Copyright 2021 Kam1runetzLabs <notsoserious2017@gmail.com>

#ifndef VECTOR_PROCESSING_INCLUDE_UTILITY_H_
#define VECTOR_PROCESSING_INCLUDE_UTILITY_H_

#include <stddef.h>
#include <stdio.h>

#include "vectors.h"

///@todo documentation
///@param vectors must be initialized
int fill_vectors(FILE *file, vectors_3d_t *vectors, size_t *read_count);

#endif  // VECTOR_PROCESSING_INCLUDE_UTILITY_H_
