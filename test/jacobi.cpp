#include "models/include/gauss_jacobi.hpp"
#include "models/include/matrix.hpp"
#include "models/include/vector.hpp"
#include <gtest/gtest.h>
#include <memory>

TEST(JacobiTest, SlideAssertion) {
  Matrix m{{{10, 2, 1}, {1, 5, 1}, {2, 3, 10}}};
  Vector v{7, -8, 6};
  auto jacobi = std::make_unique<GaussJacobi>();
  double error = 0.0001;

  jacobi->solve(m, v, error, 1000);

  Vector res = jacobi->getResult();
  Vector expected{1, -2, 1};

  for (int i = 0; i < res.getSize(); i++) {
    EXPECT_NEAR(res.getValue(i), expected.getValue(i), error);
  }
}
