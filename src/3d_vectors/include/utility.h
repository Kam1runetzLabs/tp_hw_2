// Copyright 2021 Kam1runetzLabs <notsoserious2017@gmail.com>

#ifndef _3D_VECTORS_INCLUDE_UTILITY_H_
#define _3D_VECTORS_INCLUDE_UTILITY_H_

#include <stddef.h>
#include <stdio.h>

#include "vectors.h"

///@brief заполняет векторы координатами из файла
///@param file указатель на файл с координатами, не должен быть NULL
///@param vectors указатель на структуру векторов, не должен быть NULL
///@return количество прочитанных векторов
size_t fill_vectors(FILE *file, vectors_3d_t *vectors);

#endif  // _3D_VECTORS_INCLUDE_UTILITY_H_
