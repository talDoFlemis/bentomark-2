#include "models/include/matrix.hpp"
#include "models/include/vector.hpp"

#ifndef Model_H
#define Model_H

class Model {
public:
  Vector *result;
  virtual void solve(Matrix, Vector, double, int) = 0;
  Vector getResult();
  double getError(Vector, Vector);
};

#endif
