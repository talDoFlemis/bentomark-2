#include "algebra/include/matrix.hpp"
#include "algebra/include/vector.hpp"
#include "models/include/gauss_jacobi.hpp"
#include <gtest/gtest.h>
#include <memory>

TEST(JacobiTest, SlideAssertion) {
  Algebra::Matrix m{{{10, 2, 1}, {1, 5, 1}, {2, 3, 10}}};
  Algebra::Vector v{7, -8, 6};
  auto jacobi = std::make_unique<Models::GaussJacobi>();
  double error = 0.0001;

  jacobi->solve(m, v, error, 1000);

  Algebra::Vector res = jacobi->getResult();
  Algebra::Vector expected{1, -2, 1};

  for (int i = 0; i < res.getSize(); i++) {
    EXPECT_NEAR(res.getValue(i), expected.getValue(i), error);
  }
}

TEST(JacobiTest, FourByFour) {
  Algebra::Matrix m{
      {5, -1, 0, 0}, {-1, 5, -1, 0}, {0, -1, 5, -1}, {0, 0, -1, 5}};

  Algebra::Vector v{2, 5, -4, 6};
  auto jacobi = std::make_unique<Models::GaussJacobi>();

  double error = 0.0001;

  jacobi->solve(m, v, error, 1000);

  Algebra::Vector res = jacobi->getResult();
  Algebra::Vector expected{336.0 / 551, 578.0 / 551, -201.0 / 551, 621.0 / 551};

  for (int i = 0; i < res.getSize(); i++) {
    EXPECT_NEAR(res.getValue(i), expected.getValue(i), error);
  }
}

TEST(JacobiTest, EmptyResult) {
  // TODO: testar se o resultado é vazio quando não converge
}

TEST(JacobiTest, EvalModelResult) {
  // TODO: testar se o ModelResult está correto
}
