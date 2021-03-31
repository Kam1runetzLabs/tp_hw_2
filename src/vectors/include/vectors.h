// Copyright 2021 Kam1runetzLabs <notsoserious2017@gmail.com>

#ifndef VECTORS_INCLUDE_VECTORS_H_
#define VECTORS_INCLUDE_VECTORS_H_

#include <stddef.h>
#include <stdio.h>

#include "float_array.h"

typedef struct vectors vectors_t;

///@brief инициализирует хранилище n-мерных векторов с заданной вместимостью и
///размерностью вектора
///@param capacity вместимость хранилища, не может быть 0
///@param dims размерность вектора, не может быть 0
///@return указатель на хранилище векторов или NULL в случае ошибки
vectors_t *vectors_init(size_t capacity, size_t dims);

///@brief заполняет векторы координатами из файла, если какие-то координаты
///остались не заполнены, то они считаются нулевыми
///@param file указатель на файл с координатами, не должен быть NULL
///@param vectors указатель на структуру векторов, не должен быть NULL
///@return 0 при успешном выполнении, -1 при ошибке
int vectors_fill(FILE *file, vectors_t *vectors);

///@brief добавляет вектор в хранилище векторов, если количество векторов не
///превышает вместимость хранилища
///@param vectors указатель на хранилище векторов, не может быть NULL
///@param vectors_coords указатель на вектор, размерность вектора должна быть
///равна размерности векторов в хранилище, не может быть NULL
void vectors_add_vector(vectors_t *vectors,
                        const float_array_t *vectors_coords);

///@brief возвращает массив координат заданого измерения всех векторов
///@param vectors указатель на хранилище векторов, не может быть NULL
///@param dim измерение, координаты которого запрашиваются, должно быть 0 <= dim
///< vectors_dims
///@return указатель на массив координат, возвращается не копия
float_array_t *vectors_get_coords(const vectors_t *vectors, size_t dim);

///@brief возвращает количество инициализированных векторов, изначально 0
///@param vectors указатель на хранилище векторов, не может быть NULL
///@return количество векторов
size_t vectors_count(const vectors_t *vectors);

///@param vectors указатель на хранилище векторов, не может быть NULL
///@return вместимость хранилища, задается при инициализации хранилища и не
///изменяется
size_t vectors_capacity(const vectors_t *vectors);

///@param vectors указатель на хранилище векторов, не может быть NULL
///@return размерность векторов в хранилище
size_t vectors_dims(const vectors_t *vectors);

///@brief разрушает хранилище и очищает ресурсы
///@param vectors указатель на хранилище векторов, может быть NULL
void vectors_free(vectors_t *vectors);

#endif  // VECTORS_INCLUDE_VECTORS_H_
