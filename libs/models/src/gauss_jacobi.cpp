#include "models/include/gauss_jacobi.hpp"

void GaussJacobi::solve(Matrix mat, Vector vec, double error, int maxIttr) {
  int size = mat.getSize();

  this->result = new Vector(size);
  Vector x = *result;

  Matrix C(size);
  Vector g(size);
  Vector aux(size);

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (i == j) {
        C.setValue(i, j, 0);
      } else {
        C.setValue(i, j, -mat.getValue(i, j) / mat.getValue(i, i));
      }
    }

    g.setValue(i, vec.getValue(i) / mat.getValue(i, i));
    result->setValue(i, 0);
  }

  for (int i = 0; i < maxIttr; i++) {
    aux << x;
    x = C * x + g;

    if (this->getError(x, aux) < error) {
      break;
    }
  }

  this->result = &x;
}