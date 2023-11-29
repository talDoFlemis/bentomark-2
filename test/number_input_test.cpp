#include "inputs/include/number_input.hpp"
#include <gtest/gtest.h>
#include <sstream>

TEST(NumberReaderTest, ReadValidNumber) {
  std::istringstream input("1\n");
  std::ostringstream output;
  std::ostringstream error;

  auto validator = Inspector::NumberValidator<double>("");
  validator.between(0, 10).not_equal(5);
  auto input_vector = Inputs::Number<double>(validator);
  double result = input_vector.read(input, output, error);
  double expected = 1;

  ASSERT_STREQ(error.str().c_str(), "") << "Error message should be empty";
  ASSERT_EQ(result, expected);
}

TEST(NumberReaderTest, CatchInvalidInput) {
  std::istringstream input("a\n1\n");
  std::ostringstream output;
  std::ostringstream error;

  auto validator = Inspector::NumberValidator<double>("");
  validator.between(0, 10).not_equal(5);
  auto input_vector = Inputs::Number<double>(validator);
  double result = input_vector.read(input, output, error);
  double expected = 1;

  ASSERT_STRNE(error.str().c_str(), "") << "Error message should not be empty";
  ASSERT_EQ(result, expected);
}

TEST(NumberReaderTest, CatchInvalidInputWithCustomMessage) {
  std::istringstream input("a\n1\n");
  std::ostringstream output;
  std::ostringstream error;

  auto validator = Inspector::NumberValidator<double>("Valor inválido");
  validator.between(0, 10).not_equal(5);
  auto input_vector = Inputs::Number<double>(validator);
  double result = input_vector.read(input, output, error);
  double expected = 1;

  ASSERT_STRNE(error.str().c_str(), "") << "Error message should not be empty";
  ASSERT_EQ(result, expected);
}
