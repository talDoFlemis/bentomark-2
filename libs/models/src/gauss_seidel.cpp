#include "models/include/gauss_seidel.hpp"

using namespace Models;
void GaussSeidel::solve(const Algebra::Matrix &mat, const Algebra::Vector &vec,
                        double error, int maxIttr) {

  size_t size = mat.getSize();

  this->result = std::vector<Algebra::Vector>(1, Algebra::Vector(size));
  Algebra::Vector x = result.front();

  Algebra::Vector aux(3);

  for (int i = 0; i < maxIttr; i++) {
    aux << x;

    x.setValue(0, (vec.getValue(0) - mat.getValue(0, 1) * aux.getValue(1) -
                   mat.getValue(0, 2) * aux.getValue(2)) /
                      (mat.getValue(0, 0)));

    x.setValue(1, (vec.getValue(1) - mat.getValue(1, 0) * x.getValue(0) -
                   mat.getValue(1, 2) * aux.getValue(2)) /
                      (mat.getValue(1, 1)));

    x.setValue(2, (vec.getValue(2) - mat.getValue(2, 0) * x.getValue(0) -
                   mat.getValue(2, 1) * x.getValue(1)) /
                      (mat.getValue(2, 2)));

    if (this->getError(x, aux) < error) {
      break;
    }
  }

  this->result = std::vector<Algebra::Vector>(1, x);
}
