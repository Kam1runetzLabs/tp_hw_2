// Copyright 2021 Kam1runetzLabs <notsoserious2017@gmail.com>

#include <chrono>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>

extern "C" {
#include "float_array.h"
#include "utility.h"
#include "vectors.h"
#include "vectors_calc.h"
}

int main(int argc, char *argv[]) {
  if (argc != 4) {
    std::cout << "Usage: <program> <capacity> <dims> <vectors/file/path>"
              << std::endl;
    exit(EXIT_FAILURE);
  }
  std::stringstream convert_capacity(argv[1]);
  std::stringstream convert_dims(argv[2]);

  std::size_t capacity;
  std::size_t dims;

  if (!(convert_capacity >> capacity) || !(convert_dims >> dims)) {
    std::cout << "Invalid arguments types" << std::endl;
    exit(EXIT_FAILURE);
  }

  std::string f_name(argv[3]);

  vectors_t *vectors = vectors_init(capacity, dims);
  if (!vectors) {
    std::cout << "ERROR: Fail of vectors allocation" << std::endl;
    exit(EXIT_FAILURE);
  }

  FILE *file = fopen(f_name.c_str(), "r");
  if (!file) {
    vectors_free(vectors);
    std::cout << "ERROR: Unable to open file " << f_name << std::endl;
    exit(EXIT_FAILURE);
  }

  size_t read_count = fill_vectors(file, vectors);
  if (read_count != capacity) {
    std::cout << "WARNING: read count mismatch with vectors capacity"
              << std::endl
              << "Vectors capacity: " << capacity
              << " read_count: " << read_count << std::endl;
  }
  fclose(file);

  auto start = std::chrono::high_resolution_clock::now();
  float_array_t *avg_vector = calc_avg_vector(vectors);
  auto stop = std::chrono::high_resolution_clock::now();

  if (!avg_vector) {
    std::cout << "ERROR: Fail to calculate average vector" << std::endl;
    vectors_free(vectors);
    exit(EXIT_FAILURE);
  }

  auto duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

  std::cout << std::left << "| duration: " << duration.count() << " ms |"
            << "avg_vector: ";

  const std::size_t width = 6;
  std::cout.precision(2);
  for (const_iterator it = float_array_cbegin(avg_vector);
       it != float_array_cend(avg_vector); ++it) {
    std::cout << std::left << std::setw(width) << *it << ";";
  }
  std::cout << std::endl;
  vectors_free(vectors);
  float_array_free(avg_vector);
  return 0;
}
