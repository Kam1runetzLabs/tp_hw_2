// Copyright 2021 Kam1runetzLabs <notsoserious2017@gmail.com>

#ifndef FLOAT_ARRAY_INCLUDE_FLOAT_ARRAY_H_
#define FLOAT_ARRAY_INCLUDE_FLOAT_ARRAY_H_

#include <stddef.h>

typedef struct float_array float_array_t;
typedef float *iterator;
typedef const float *const_iterator;

///@brief создает на динамической памяти массив float с заданым количеством
///элементов
///@param size количество элементов массива, не может быть 0
///@return указатель на массив или NULL в случае ошибки
float_array_t *float_array_init(size_t size);

///@brief разрушает массив и чистит ресурсы
///@param array указатель на удаляемый массив, может быть NULL
void float_array_free(float_array_t *array);

///@param array указатель на массив, не может быть NULL
///@return размер массива, 0 в случае если передан NULL
size_t float_array_size(const float_array_t *array);

///@param array указатель на массив, не может быть NULL
///@return указатель на начало массива, NULL в случае ошибки
iterator float_array_begin(const float_array_t *array);

///@param array указатель на массив, не может быть NULL
///@return указатель на конец массива (begin + size), NULL в случае ошибки
iterator float_array_end(const float_array_t *array);

///@param array указатель на массив, не может быть NULL
///@return константный указатель на начало массива, NULL в случае ошибки
const_iterator float_array_cbegin(const float_array_t *array);

///@param array указатель на массив, не может быть NULL
///@return константный указатель на конец массива (begin + size), NULL в случае
///ошибки
const_iterator float_array_cend(const float_array_t *array);

///@param array указатель на массив, не может быть NULL
///@param index индекс элемента, должен быть 0 <= index < array_size
///@param element указатель на элемент, в который будет занесено значение
///@return 0 в случае успеха, -1 в случае ошибки
int float_array_get_element(const float_array_t *array, size_t index,
                            float *element);

///@param array указатель на массив, не может быть NULL
///@param index индекс элемента, должен быть 0 <= index < array_size
///@param value значение элемента
///@return 0 в случае успеха, -1 в случае ошибки
int float_array_set_element(float_array_t *array, size_t index, float value);

#endif  // FLOAT_ARRAY_INCLUDE_FLOAT_ARRAY_H_
