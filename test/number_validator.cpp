#include "inspector/include/number_validator.hpp"
#include <gtest/gtest.h>

TEST(NumberValidatorTest, IntegerValidation) {
  auto validator = Inspector::NumberValidator<int>("42");

  EXPECT_TRUE(validator.validate());
  EXPECT_TRUE(validator.get_error_messages().empty());
}

TEST(NumberValidatorTest, FloatValidation) {
  auto validator = Inspector::NumberValidator<float>("3.14");

  EXPECT_TRUE(validator.validate());
  EXPECT_TRUE(validator.get_error_messages().empty());
}

TEST(NumberValidatorTest, EmptyInput) {
  auto validator = Inspector::NumberValidator<float>("");

  EXPECT_FALSE(validator.validate());
  EXPECT_FALSE(validator.get_error_messages().empty());
}

TEST(NumberValidatorTest, InvalidInput) {
  auto validator = Inspector::NumberValidator<int>("invalid");

  EXPECT_FALSE(validator.validate());
  EXPECT_FALSE(validator.get_error_messages().empty());
}

TEST(NumberValidatorTest, Between) {
  auto validator = Inspector::NumberValidator<int>("42");

  validator.between(0, 100);

  EXPECT_TRUE(validator.validate());
  EXPECT_TRUE(validator.get_error_messages().empty());
}

TEST(NumberValidatorTest, BetweenInvalid) {
  auto validator = Inspector::NumberValidator<int>("42");

  validator.between(0, 10);

  EXPECT_FALSE(validator.validate());
  EXPECT_FALSE(validator.get_error_messages().empty());
}

TEST(NumberValidatorTest, GreaterThan) {
  auto validator = Inspector::NumberValidator<int>("42");

  validator.greaterThan(0);

  EXPECT_TRUE(validator.validate());
  EXPECT_TRUE(validator.get_error_messages().empty());
}

TEST(NumberValidatorTest, GreaterThanInvalid) {
  auto validator = Inspector::NumberValidator<int>("42");

  validator.greaterThan(100);

  EXPECT_FALSE(validator.validate());
  EXPECT_FALSE(validator.get_error_messages().empty());
}

TEST(NumberValidatorTest, LessThan) {
  auto validator = Inspector::NumberValidator<int>("42");

  validator.lessThan(100);

  EXPECT_TRUE(validator.validate());
  EXPECT_TRUE(validator.get_error_messages().empty());
}

TEST(NumberValidatorTest, LessThanInvalid) {
  auto validator = Inspector::NumberValidator<int>("42");

  validator.lessThan(0);

  EXPECT_FALSE(validator.validate());
  EXPECT_FALSE(validator.get_error_messages().empty());
}

TEST(NumberValidatorTest, Equal) {
  auto validator = Inspector::NumberValidator<int>("42");

  validator.equal(42);

  EXPECT_TRUE(validator.validate());
  EXPECT_TRUE(validator.get_error_messages().empty());
}

TEST(NumberValidatorTest, EqualInvalid) {
  auto validator = Inspector::NumberValidator<int>("42");

  validator.equal(0);

  EXPECT_FALSE(validator.validate());
  EXPECT_FALSE(validator.get_error_messages().empty());
}

TEST(NumberValidatorTest, NotEqual) {
  auto validator = Inspector::NumberValidator<int>("42");

  validator.not_equal(0);

  EXPECT_TRUE(validator.validate());
  EXPECT_TRUE(validator.get_error_messages().empty());
}

TEST(NumberValidatorTest, NotEqualInvalid) {
  auto validator = Inspector::NumberValidator<int>("42");

  validator.not_equal(42);

  EXPECT_FALSE(validator.validate());
  EXPECT_FALSE(validator.get_error_messages().empty());
}

TEST(NumberValidatorTest, MultipleConstraints) {
  auto validator = Inspector::NumberValidator<int>("42");

  validator.between(0, 100).greaterThan(0).lessThan(100).equal(42).not_equal(0);

  EXPECT_TRUE(validator.validate());
  EXPECT_TRUE(validator.get_error_messages().empty());
}

TEST(NumberValidatorTest, MultipleConstraintsInvalid) {
  auto validator = Inspector::NumberValidator<int>("42");

  validator.between(0, 10).greaterThan(100).lessThan(0).equal(0).not_equal(42);

  EXPECT_FALSE(validator.validate());
  EXPECT_FALSE(validator.get_error_messages().empty());
  EXPECT_EQ(validator.get_error_messages().size(), 5);
}

TEST(NumberValidatorTest, GetValue) {
  auto validator = Inspector::NumberValidator<int>("42");

  EXPECT_EQ(validator.get_value(), 42);
  EXPECT_TRUE(validator.get_error_messages().empty());
}

TEST(NumberValidatorTest, SetValue) {
  auto validator = Inspector::NumberValidator<int>("42");

  validator.set_value("0");

  EXPECT_EQ(validator.get_value(), 0);
  EXPECT_TRUE(validator.get_error_messages().empty());
}

TEST(NumberValidatorTest, SetValueInvalid) {
  auto validator = Inspector::NumberValidator<int>("42");

  validator.set_value("invalid");

  EXPECT_EQ(validator.get_value(), 42);
  EXPECT_FALSE(validator.get_error_messages().empty());
}

TEST(NumberValidatorTest, TestStringWithSpaces) {
  auto validator = Inspector::NumberValidator<int>("1 2 3 4");

  EXPECT_FALSE(validator.validate());
  EXPECT_FALSE(validator.get_error_messages().empty());
}

TEST(NumberValidatorTest, TestStringWithNewLines) {
  auto validator = Inspector::NumberValidator<int>("42 42\n\n");

  EXPECT_FALSE(validator.validate());
  EXPECT_FALSE(validator.get_error_messages().empty());
}

TEST(NumberValidatorTest, TestStringWithTabs) {
  auto validator = Inspector::NumberValidator<int>("42\t42");

  EXPECT_FALSE(validator.validate());
  EXPECT_FALSE(validator.get_error_messages().empty());
}

TEST(NumberValidatorTest, TestStringWithLetters) {
  auto validator = Inspector::NumberValidator<int>("42a");

  EXPECT_FALSE(validator.validate());
  EXPECT_FALSE(validator.get_error_messages().empty());
}

TEST(NumberValidatorTest, TestStringWithSymbols) {
  auto validator = Inspector::NumberValidator<int>("42@");

  EXPECT_FALSE(validator.validate());
  EXPECT_FALSE(validator.get_error_messages().empty());
}

TEST(NumberValidatorTest, TestStringWithNegative) {
  auto validator = Inspector::NumberValidator<int>("-42");

  EXPECT_TRUE(validator.validate());
  EXPECT_TRUE(validator.get_error_messages().empty());
}

TEST(NumberValidatorTest, TestWithResetValue) {
  auto validator = Inspector::NumberValidator<int>("");

  EXPECT_FALSE(validator.validate());
  EXPECT_FALSE(validator.get_error_messages().empty());

  validator.set_value("42");

  EXPECT_TRUE(validator.validate());
  EXPECT_TRUE(validator.get_error_messages().empty());
}

TEST(NumberValidatorTest, TestCientificNotation) {
  auto validator = Inspector::NumberValidator<double>("1e-10");

  EXPECT_TRUE(validator.validate());
  EXPECT_TRUE(validator.get_error_messages().empty());
  EXPECT_EQ(validator.get_value(), 1e-10);
}

TEST(NumberValidatorTest, TestSizeT) {
  auto validator = Inspector::NumberValidator<size_t>("42");

  EXPECT_TRUE(validator.validate());
  EXPECT_TRUE(validator.get_error_messages().empty());
  EXPECT_EQ(validator.get_value(), 42);
}

TEST(NumberValidatorTest, TestSizeTInvalid) {
  auto validator = Inspector::NumberValidator<size_t>("-42");

  EXPECT_FALSE(validator.validate());
  EXPECT_FALSE(validator.get_error_messages().empty());
}
