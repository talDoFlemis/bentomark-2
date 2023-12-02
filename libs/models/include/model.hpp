#ifndef Model_H
#define Model_H

#include "algebra/include/matrix.hpp"
#include "algebra/include/vector.hpp"

namespace Models {
class Model {
public:
  virtual ~Model() = default;

  std::vector<Algebra::Vector> result;
  virtual void solve(const Algebra::Matrix &, const Algebra::Vector &, double,
                     int) = 0;
  Algebra::Matrix solveInverse(const Algebra::Matrix &, double, int);
  Algebra::Vector getResult() const;
  double getError(const Algebra::Vector &, const Algebra::Vector &) const;
};
}; // namespace Models

#endif
