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
    double auxValue;

    for (int j = 0; j < size; j++) {
        auxValue = vec.getValue(j);
        for (int k = 0; k < size; k++) {
            if (j < k) {
                auxValue -= mat.getValue(j, k) * aux.getValue(k);
            } else if (j > k) {
                auxValue -= mat.getValue(j, k) * x.getValue(k);
            }
        }

      x.setValue(j, (auxValue) / (mat.getValue(j, j)));
    }

    if (this->getError(x, aux) < error) {
      break;
    }
  }

  this->result = std::vector<Algebra::Vector>(1, x);
}
