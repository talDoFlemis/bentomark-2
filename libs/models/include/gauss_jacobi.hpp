#ifndef GAUSS_JACOBI_H
#define GAUSS_JACOBI_H

#include "models/include/model.hpp"

namespace Models {
class GaussJacobi : public Model {
public:
  void solve(const Algebra::Matrix &, const Algebra::Vector &, double,
             int) override;
};
}; // namespace Models

#endif // !GAUSS_JACOBI_H
