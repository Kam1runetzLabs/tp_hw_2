// Copyright 2021 Kam1runetzLabs <notsoserious2017@gmail.com>

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "float_array.h"
#include "vectors.h"
#include "vectors_calc.h"

int main(int argc, char *argv[]) {
  if (argc != 4) {
    fprintf(stderr,
            "usage: <program> <vectors_capacity> <dims> <vectors_file>\n");
    exit(EXIT_FAILURE);
  }

  size_t vectors_cap = atoi(argv[1]);
  size_t vectors_dims = atoi(argv[2]);

  if (vectors_cap == 0 || vectors_dims == 0) {
    fprintf(stderr, "invalid integer arguments was transmitted\n");
    exit(EXIT_FAILURE);
  }

  vectors_t *vectors = vectors_init(vectors_cap, vectors_dims);
  if (!vectors) {
    fprintf(stderr, "internal allocation error\n");
    exit(EXIT_FAILURE);
  }

  FILE *v_file = fopen(argv[3], "r");
  if (!v_file) {
    fprintf(stderr, "unable to open vectors file\n");
    vectors_free(vectors);
    exit(EXIT_FAILURE);
  }

  int error = vectors_fill(v_file, vectors);
  if (error) {
    fclose(v_file);
    fprintf(stderr, "invalid vectors file\n");
    vectors_free(vectors);
    exit(EXIT_FAILURE);
  }
  fclose(v_file);

  struct timeval start, end;
  gettimeofday(&start, NULL);
  float_array_t *avg_vector = calc_avg_vector(vectors);
  gettimeofday(&end, NULL);
  if (!avg_vector) {
    fprintf(stderr, "internal allocation error\n");
    vectors_free(vectors);
    exit(EXIT_FAILURE);
  }
  size_t seconds = end.tv_sec - start.tv_sec;
  size_t microsec = seconds * 1000000 + end.tv_usec - start.tv_usec;
  printf("time: %lu s (%lu microsec) | ", seconds, microsec);
  printf("avg_vector: ");
  const_iterator avg_vector_begin = float_array_cbegin(avg_vector);
  const_iterator avg_vector_end = float_array_cend(avg_vector);
  for (const_iterator it = avg_vector_begin; it != avg_vector_end; ++it)
    printf("%f;", *it);
  printf("\n");

  vectors_free(vectors);
  float_array_free(avg_vector);
  return 0;
}
