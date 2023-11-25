#include "models/include/vector.hpp"

#ifndef Matrix_H
#define Matrix_H

class Matrix {
private:
  int size;
  double *values;

public:
  Matrix(int);
  int getSize();
  void setValue(int, int, double);
  double getValue(int, int);
  void printMatrix();

  Vector operator*(Vector);
};

#endif