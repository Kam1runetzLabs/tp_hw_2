// Copyright 2021 Kam1runetzLabs <notsoserious2017@gmail.com>

#ifndef VECTOR_PROCESSING_INCLUDE_UTILITY_H_
#define VECTOR_PROCESSING_INCLUDE_UTILITY_H_

#include <stddef.h>
#include <stdio.h>

#include "vectors.h"

///@brief заполняет векторы координатами из файла
///@param file указатель на файл с координатами, не должен быть NULL
///@param vectors указатель на структуру векторов, не должен быть NULL
///@return количество прочитанных векторов
size_t fill_vectors(FILE *file, vectors_3d_t *vectors);

#endif  // VECTOR_PROCESSING_INCLUDE_UTILITY_H_
