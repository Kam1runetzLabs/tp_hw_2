// Copyright 2021 Kam1runetzLabs <notsoserious2017@gmail.com>

#include <stddef.h>
#include <stdlib.h>

#include "vectors_calc.h"
#include "float_array.h"
#include "thread_pool.h"
#include "vectors.h"

typedef struct {
  float_array_t *coords_range;
  float *avg_coord_ptr;
  size_t vectors_count;
} args_t;

static void *float_range_avg(void *arg) {
  args_t *args = arg;
  float common = 0.f;
  const_iterator begin = float_array_cbegin(args->coords_range);
  const_iterator end = float_array_cend(args->coords_range);
  for (const_iterator it = begin; it != end; ++it) common += *it;
  *args->avg_coord_ptr = common / (float)args->vectors_count;
  return NULL;
}

float_array_t *calc_avg_vector(const vectors_t *vectors) {
  if (!vectors) return NULL;
  thread_pool_t *pool = thread_pool_init(hardware_concurrency());
  if (!pool) return NULL;

  size_t v_dims = vectors_dims(vectors);

  float_array_t *avg_vector = float_array_init(v_dims);
  if (!avg_vector) {
    thread_pool_cancel_and_destroy(pool);
    return NULL;
  }

  args_t *args_array = (args_t *)malloc(sizeof(args_t) * v_dims);
  if (!args_array) {
    thread_pool_cancel_and_destroy(pool);
    float_array_free(avg_vector);
    return NULL;
  }

  for (size_t i = 0; i != v_dims; ++i) {
    args_array[i].coords_range = vectors_get_coords(vectors, i);
    args_array[i].vectors_count = vectors_count(vectors);
    args_array[i].avg_coord_ptr = float_array_begin(avg_vector) + i;
  }

  for (size_t i = 0; i != v_dims; ++i) {
    int err =
        thread_pool_enqueue_task(pool, float_range_avg, &args_array[i], NULL);
    if (err) {
      thread_pool_cancel_and_destroy(pool);
      free(args_array);
      float_array_free(avg_vector);
      return NULL;
    }
  }
  thread_pool_wait_and_destroy(pool);
  return avg_vector;
}
