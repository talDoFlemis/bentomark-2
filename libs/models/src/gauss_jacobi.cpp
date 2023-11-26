#include "models/include/gauss_jacobi.hpp"

using namespace Models;
void GaussJacobi::solve(const Algebra::Matrix &mat, const Algebra::Vector &vec,
                        double error, int maxIttr) {
  size_t size = mat.getSize();

  this->result = std::vector<Algebra::Vector>(1, Algebra::Vector(size));
  Algebra::Vector x = result.front();

  Algebra::Matrix C(size);
  Algebra::Vector g(size);
  Algebra::Vector aux(size);

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (i == j) {
        C.setValue(i, j, 0);
      } else {
        C.setValue(i, j, -mat.getValue(i, j) / mat.getValue(i, i));
      }
    }

    g.setValue(i, vec.getValue(i) / mat.getValue(i, i));
    result.front().setValue(i, g.getValue(i));
  }

  for (int i = 0; i < maxIttr; i++) {
    aux << x;
    x = C * x + g;

    if (this->getError(x, aux) < error) {
      break;
    }
  }

  this->result = std::vector<Algebra::Vector>(1, x);
}
