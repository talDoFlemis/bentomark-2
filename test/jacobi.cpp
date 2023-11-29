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