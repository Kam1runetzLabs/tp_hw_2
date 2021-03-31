// Copyright 2021 Kam1runetzLabs <notsoserious2017@gmail.com>

#include <gtest/gtest.h>

#include <ctime>
#include <fstream>

extern "C" {
#include "vectors.h"
}

const size_t capacity = 123;
const size_t dims = 3;
const size_t invalid_capacity = -1;
const size_t invalid_dims = -1;

TEST(VectorsInit, Init) {
  vectors_t *vectors = vectors_init(capacity, dims);
  EXPECT_TRUE(vectors);
  EXPECT_EQ(capacity, vectors_capacity(vectors));
  EXPECT_EQ(dims, vectors_dims(vectors));
  vectors_free(vectors);
}

TEST(VectorsInit, InvalidCapacityInit) {
  vectors_t *vectors = vectors_init(invalid_capacity, dims);
  EXPECT_FALSE(vectors);
}

TEST(VectorsInit, InvalidDimsInit) {
  vectors_t *vectors = vectors_init(capacity, invalid_dims);
  EXPECT_FALSE(vectors);
}

TEST(VectorsInit, NullCapacityInit) {
  EXPECT_EXIT(vectors_init(0, dims), ::testing::KilledBySignal(SIGABRT), "");
}

TEST(VectorsInit, NullDimsInit) {
  EXPECT_EXIT(vectors_init(capacity, 0), ::testing::KilledBySignal(SIGABRT),
              "");
}

TEST(VectorsGetCoords, GetCoords) {
  vectors_t *vectors = vectors_init(capacity, dims);
  const size_t dim = 0;
  float_array_t *coords_line = vectors_get_coords(vectors, dim);
  EXPECT_TRUE(coords_line);
  for (const_iterator it = float_array_cbegin(coords_line);
       it != float_array_cend(coords_line); ++it) {
    EXPECT_FLOAT_EQ(0.f, *it);
  }
  vectors_free(vectors);
}

TEST(VectorsGetCoords, GetCoordsFromNullVectors) {
  vectors_t *vectors = nullptr;
  const size_t dim = 0;
  EXPECT_EXIT(vectors_get_coords(vectors, dim),
              ::testing::KilledBySignal(SIGABRT), "");
}

TEST(VectorsGetCoords, GetCoordsFromInvalidDim) {
  vectors_t *vectors = vectors_init(capacity, dims);
  const size_t dim = dims;
  EXPECT_EXIT(vectors_get_coords(vectors, dim),
              ::testing::KilledBySignal(SIGABRT), "");
  vectors_free(vectors);
}

TEST(VectorsAddVector, VectorsAddVector) {
  static unsigned int seed = time(nullptr);
  vectors_t *vectors = vectors_init(capacity, dims);
  float_array_t *new_vector = float_array_init(dims);

  for (iterator it = float_array_begin(new_vector);
       it != float_array_end(new_vector); ++it)
    *it = static_cast<float>(rand_r(&seed));

  vectors_add_vector(vectors, new_vector);
  float_array_t *coords[dims];

  for (size_t i = 0; i != dims; ++i) coords[i] = vectors_get_coords(vectors, i);

  for (size_t i = 0; i != dims; ++i)
    EXPECT_FLOAT_EQ(float_array_get_element(new_vector, i),
                    float_array_get_element(coords[i], 0));
  vectors_free(vectors);
  float_array_free(new_vector);
}

TEST(VectorsAddVector, VectorsAddVectorToNullVectors) {
  vectors_t *vectors = nullptr;
  float_array_t *new_vector = float_array_init(dims);
  EXPECT_EXIT(vectors_add_vector(vectors, new_vector),
              ::testing::KilledBySignal(SIGABRT), "");
  float_array_free(new_vector);
}

TEST(VectorsAddVector, VectorsAddNullVector) {
  vectors_t *vectors = vectors_init(capacity, dims);
  float_array_t *new_vector = nullptr;
  EXPECT_EXIT(vectors_add_vector(vectors, new_vector),
              ::testing::KilledBySignal(SIGABRT), "");
  vectors_free(vectors);
}

TEST(VectorsAddVector, VectorsAddInvalidVector) {
  vectors_t *vectors = vectors_init(capacity, dims);
  float_array_t *new_vector = float_array_init(dims + 1);
  EXPECT_EXIT(vectors_add_vector(vectors, new_vector),
              ::testing::KilledBySignal(SIGABRT), "");
  vectors_free(vectors);
  float_array_free(new_vector);
}

TEST(VectorsAddVector, AddVectorToFullVectors) {
  vectors_t *vectors = vectors_init(capacity, dims);
  for (size_t i = 0; i != capacity; ++i) {
    float_array_t *new_vector = float_array_init(dims);
    vectors_add_vector(vectors, new_vector);
    float_array_free(new_vector);
  }

  float_array_t *new_vector = float_array_init(dims);
  EXPECT_EXIT(vectors_add_vector(vectors, new_vector),
              ::testing::KilledBySignal(SIGABRT), "");
  float_array_free(new_vector);
  vectors_free(vectors);
}

TEST(VectorsCount, VectorsCount) {
  vectors_t *vectors = vectors_init(capacity, dims);
  EXPECT_EQ(vectors_count(vectors), 0);
  float_array_t *new_vector = float_array_init(dims);
  vectors_add_vector(vectors, new_vector);
  float_array_free(new_vector);
  EXPECT_EQ(vectors_count(vectors), 1);
  vectors_free(vectors);
}

TEST(VectorsCount, VectorsCountFromNullVectors) {
  vectors_t *vectors = nullptr;
  EXPECT_EXIT(vectors_count(vectors), ::testing::KilledBySignal(SIGABRT), "");
}

TEST(VectorsCapacity, VectorsCapacity) {
  vectors_t *vectors = vectors_init(capacity, dims);
  EXPECT_EQ(capacity, vectors_capacity(vectors));
  vectors_free(vectors);
}

TEST(VectorsCapacity, NullVectorsCapacity) {
  vectors_t *vectors = nullptr;
  EXPECT_EXIT(vectors_capacity(vectors), ::testing::KilledBySignal(SIGABRT),
              "");
}

TEST(VectorsDims, VectorsDims) {
  vectors_t *vectors = vectors_init(capacity, dims);
  EXPECT_EQ(dims, vectors_dims(vectors));
  vectors_free(vectors);
}

TEST(VectorsDims, NullVectorsDims) {
  vectors_t *vectors = nullptr;
  EXPECT_EXIT(vectors_dims(vectors), ::testing::KilledBySignal(SIGABRT), "");
}

static void fill_vectors_file(const std::string &fname) {
  static unsigned int seed = time(nullptr);
  std::ofstream file_stream{fname};
  for (size_t i = 0; i != dims; ++i) {
    for (size_t j = 0; j != capacity; ++j)
      file_stream << static_cast<float>(rand_r(&seed)) << " ";
    file_stream << "\n";
  }
  file_stream.close();
}

static void remove_file(const std::string &fname) { remove(fname.c_str()); }

TEST(FillVectors, FillVectors) {
  const std::string fname("vectors.txt");
  fill_vectors_file(fname);
  vectors_t *vectors = vectors_init(capacity, dims);
  FILE *file = fopen(fname.c_str(), "r");
  int error = vectors_fill(file, vectors);
  fclose(file);
  remove_file(fname);
  EXPECT_FALSE(error);
  vectors_free(vectors);
}

TEST(FillVectors, FillVectorsFromNullFile) {
  FILE *file = nullptr;
  vectors_t *vectors = vectors_init(capacity, dims);
  EXPECT_EXIT(vectors_fill(file, vectors), ::testing::KilledBySignal(SIGABRT),
              "");
  vectors_free(vectors);
}

TEST(FillVectors, FillNullVectors) {
  const std::string fname("vectors.txt");
  fill_vectors_file(fname);
  vectors_t *vectors = nullptr;
  FILE *file = fopen(fname.c_str(), "r");
  EXPECT_EXIT(vectors_fill(file, vectors), ::testing::KilledBySignal(SIGABRT),
              "");
  fclose(file);
  remove_file(fname);
}

static void fill_invalid_vectors_file(const std::string &fname) {
  static unsigned int seed = time(nullptr);
  std::ofstream file_stream{fname};
  for (size_t i = 0; i != dims; ++i) {
    for (size_t j = 0; j != capacity; ++j)
      if (j % 2 == 0)
        file_stream << static_cast<float>(rand_r(&seed)) << " ";
      else
        file_stream << static_cast<char>(rand_r(&seed)) << " ";
    file_stream << "\n";
  }
  file_stream.close();
}

TEST(FillVectors, FillFromInvalidFile) {
  const std::string fname("invalid_vectors.txt");
  fill_invalid_vectors_file(fname);
  vectors_t *vectors = vectors_init(capacity, dims);
  FILE *file = fopen(fname.c_str(), "r");
  int error = vectors_fill(file, vectors);
  fclose(file);
  EXPECT_TRUE(error);
  EXPECT_EQ(vectors_count(vectors), 0);
  remove_file(fname);
}
