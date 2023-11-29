#include "inputs/include/matrix.hpp"
#include "algebra/include/matrix.hpp"
#include <gtest/gtest.h>
#include <sstream>

TEST(MatrixReaderTest, ReadValidMatrix) {
  std::istringstream input("1\n2\n3\n4\n5\n6\n7\n8\n9\n");
  std::ostringstream output;
  std::ostringstream error;
  size_t size = 3;

  auto input_matrix = Inputs::Matrix(size);
  Algebra::Matrix result = input_matrix.read(input, output, error);
  auto expected = Algebra::Matrix{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

  ASSERT_STREQ(error.str().c_str(), "") << "Error message should be empty";

  for (size_t i = 0; i < size; i++) {
    for (size_t j = 0; j < size; j++) {
      ASSERT_EQ(result.getValue(i, j), expected.getValue(i, j));
    }
  }
}

TEST(MatrixReaderTest, CatchInputUntilNewline) {
  std::istringstream input("1 2 3\n1\n2\n3\n4\n");
  std::ostringstream output;
  std::ostringstream error;
  size_t size = 2;

  auto input_matrix = Inputs::Matrix(size);
  Algebra::Matrix result = input_matrix.read(input, output, error);
  auto expected = Algebra::Matrix{{1, 2}, {3, 4}};

  ASSERT_STRNE(error.str().c_str(), "") << "Error message should not be empty";

  for (size_t i = 0; i < size; i++) {
    for (size_t j = 0; j < size; j++) {
      ASSERT_EQ(result.getValue(i, j), expected.getValue(i, j));
    }
  }
}

TEST(MatrixReaderTest, CatchInvalidInput) {
  std::istringstream input("1\n2\na\n3\n4");
  std::ostringstream output;
  std::ostringstream error;
  size_t size = 2;

  auto input_matrix = Inputs::Matrix(size);
  Algebra::Matrix result = input_matrix.read(input, output, error);
  auto expected = Algebra::Matrix{{1, 2}, {3, 4}};

  ASSERT_STRNE(error.str().c_str(), "") << "Error message should not be empty";

  for (size_t i = 0; i < size; i++) {
    for (size_t j = 0; j < size; j++) {
      ASSERT_EQ(result.getValue(i, j), expected.getValue(i, j));
    }
  }
}
