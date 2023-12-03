#ifndef Model_H
#define Model_H

#include "algebra/include/matrix.hpp"
#include "algebra/include/vector.hpp"
#include "Model_Result.hpp"

namespace Models {
class Model {
public:
  virtual ~Model() = default;
  
  Model_Result results;
  void set_model_result(const Algebra::Vector &vec1, const Algebra::Vector &vec2);
  Model_Result get_model_result() const;
  std::vector<Algebra::Vector> result;
  virtual void solve(const Algebra::Matrix &, const Algebra::Vector &, double,
                     int) = 0;
  Algebra::Matrix solveInverse(const Algebra::Matrix &, double, int);
  Algebra::Vector getResult() const;
  double getError(const Algebra::Vector &, const Algebra::Vector &) const;
};
}; // namespace Models

#endif
