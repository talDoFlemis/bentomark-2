#include "algebra/include/vector.hpp"
#include "inputs/include/vector.hpp"
#include <gtest/gtest.h>
#include <sstream>

TEST(VectorReaderTest, ReadValidVector) {
  std::istringstream input("1\n2\n3\n");
  std::ostringstream output;
  std::ostringstream error;
  size_t size = 3;

  auto input_vector = Inputs::Vector(size);
  Algebra::Vector result = input_vector.read(input, output, error);
  auto expected = Algebra::Vector{1, 2, 3};

  ASSERT_STREQ(error.str().c_str(), "") << "Error message should be empty";

  for (size_t i = 0; i < size; i++) {
    for (size_t j = 0; j < size; j++) {
      ASSERT_EQ(result.getValue(i), expected.getValue(i));
    }
  }
}

TEST(VectorReaderTest, CatchInputUntilNewline) {
  std::istringstream input("1 2 3\n1\n2\n");
  std::ostringstream output;
  std::ostringstream error;
  size_t size = 2;

  auto input_vector = Inputs::Vector(size);
  Algebra::Vector result = input_vector.read(input, output, error);
  auto expected = Algebra::Vector{1, 2};

  ASSERT_STRNE(error.str().c_str(), "") << "Error message should not be empty";

  for (size_t i = 0; i < size; i++) {
    for (size_t j = 0; j < size; j++) {
      ASSERT_EQ(result.getValue(i), expected.getValue(i));
    }
  }
}

TEST(VectorReaderTest, CatchInvalidInput) {
  std::istringstream input("1\n2\na\n3\n4\n");
  std::ostringstream output;
  std::ostringstream error;
  size_t size = 4;

  auto input_vector = Inputs::Vector(size);
  Algebra::Vector result = input_vector.read(input, output, error);
  auto expected = Algebra::Vector{1, 2, 3, 4};

  ASSERT_STRNE(error.str().c_str(), "") << "Error message should not be empty";

  for (size_t i = 0; i < size; i++) {
    for (size_t j = 0; j < size; j++) {
      ASSERT_EQ(result.getValue(i), expected.getValue(i));
    }
  }
}
