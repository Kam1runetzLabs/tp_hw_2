// Copyright 2021 Kam1runetzLabs <notsoserious2017@gmail.com>

#include <chrono>
#include <cstdlib>
#include <iostream>

extern "C" {
#include "float_array.h"
#include "utility.h"
#include "vectors.h"
#include "vectors_calc.h"
}

// todo switch fprintf to cout
// todo arsg handiling

int main(int argc, char *argv[]) {
  const size_t capacity = 123;
  const size_t dims = 3;
  std::string f_name;

  vectors_t *vectors = vectors_init(capacity, dims);
  if (!vectors) {
    fprintf(stderr, "ERROR: Fail of vectors allocation\n");
    exit(EXIT_FAILURE);
  }

  FILE *file = fopen(f_name.c_str(), "r");
  if (!file) {
    vectors_free(vectors);
    fprintf(stderr, "ERROR: Unable to open file %s\n", f_name.c_str());
    exit(EXIT_FAILURE);
  }

  size_t read_count = fill_vectors(file, vectors);
  if (read_count != capacity) {
    fprintf(stderr,
            "WARNING: read count mismatch with vectors capacity\nVectors "
            "capacity: %lu, read_count: %lu\n",
            capacity, read_count);
  }

  auto start = std::chrono::high_resolution_clock::now();
  float_array_t *avg_vector = calc_avg_vector(vectors);
  auto stop = std::chrono::high_resolution_clock::now();

  if (!avg_vector) {
    fprintf(stderr, "ERROR: Fail to calculate average vector\n");
    vectors_free(vectors);
    exit(EXIT_FAILURE);
  }

  auto duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
  vectors_free(vectors);
  float_array_free(avg_vector);

  std::cout << "duration: " << duration.count() << "ms" << std::endl;
  return 0;
}