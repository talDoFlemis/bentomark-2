#include "algebra/include/matrix.hpp"
#include "algebra/include/vector.hpp"
#include <gtest/gtest.h>

TEST(MatrixTest, Test2By2Pivoting) {
  Algebra::Matrix A{{0, 2}, {-1, 0}};
  Algebra::Vector b{1, 1};
  Algebra::Matrix expected{{-1, 0}, {0, 2}};

  EXPECT_FALSE(A.checkLineCriteria());

  Algebra::Matrix pivoted = A.pivote_max();
  EXPECT_TRUE(pivoted.checkLineCriteria());
  for (int i = 0; i < pivoted.getSize(); i++) {
    for (int j = 0; j < pivoted.getSize(); j++) {
      EXPECT_EQ(pivoted.getValue(i, j), expected.getValue(i, j));
    }
  }
}
