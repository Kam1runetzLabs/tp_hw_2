// Copyright 2021 Kam1runetzLabs <notsoserious2017@gmail.com>

#ifndef SYNC_VECTORS_CALCULATING_INCLUDE_VECTORS_CALC_H_
#define SYNC_VECTORS_CALCULATING_INCLUDE_VECTORS_CALC_H_

#include "float_array.h"
#include "vectors.h"

///@brief из структуры n-мерных векторов считает в одном потоке n-мерный
///вектор со средними координатами
///@param vectors указатель на структуру векторов, не может быть NULL
///@return указатель на вектор со средними координатами, NULL в случае ошибки
float_array_t *calc_avg_vector(const vectors_t *vectors);

#endif  // SYNC_VECTORS_CALCULATING_INCLUDE_VECTORS_CALC_H_
