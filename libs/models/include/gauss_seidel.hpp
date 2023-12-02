#ifndef GAUSS_SEIDEL_H
#define GAUSS_SEIDEL_H

#include "algebra/include/matrix.hpp"
#include "models/include/model.hpp"

namespace Models {
class GaussSeidel : public Model {
public:
  void solve(const Algebra::Matrix &, const Algebra::Vector &, double,
             int) override;
};
}; // namespace Models

#endif // !GAUSS_SEIDEL_H
