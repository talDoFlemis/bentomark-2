#include "models/include/matrix.hpp"
#include "models/include/vector.hpp"

#ifndef Model_H
#define Model_H

class Model {
public:
  virtual ~Model() = default;

  std::vector<Vector> result;
  virtual void solve(const Matrix &, const Vector &, double, int) = 0;
  Vector getResult() const;
  double getError(const Vector &, const Vector &) const;
};

#endif
