#include "models/include/matrix.hpp"
#include "models/include/model.hpp"
#include "models/include/gauss_jacobi.hpp"
#include <iostream>

int main(int argc, char *argv[]) {

  /*
  Caso teste do slide

  Resultado esperado = [1, -2, 1]
  */

  Matrix m(3);
  
  m.setValue(0, 0, 10);
  m.setValue(0, 1, 2);
  m.setValue(0, 2, 1);
  m.setValue(1, 0, 1);
  m.setValue(1, 1, 5);
  m.setValue(1, 2, 1);
  m.setValue(2, 0, 2);
  m.setValue(2, 1, 3);
  m.setValue(2, 2, 10);

  Vector v(3);

  v.setValue(0, 7);
  v.setValue(1, -8);
  v.setValue(2, 6);

  Model* jacobi = new GaussJacobi();

  jacobi->solve(m, v, 0.0001, 1000);

  Vector v2 = jacobi->getResult();
  v2.printVector();
  return 0;
}
