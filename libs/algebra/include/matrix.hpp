#ifndef Matrix_H
#define Matrix_H

#include "algebra/include/vector.hpp"
#include <cstddef>
#include <initializer_list>
#include <vector>

namespace Algebra {
class Matrix {
private:
  size_t size;
  std::vector<double> values;

public:
  explicit Matrix(size_t);
  explicit Matrix(std::initializer_list<std::initializer_list<double>> &&);

  // getter and setter
  size_t getSize() const;
  void setValue(size_t, size_t, double);
  double getValue(size_t, size_t) const;
  void printMatrix();

  // related algorithms

  // Pivote lines to make them have the max pivote possible.
  // This operation have a complexity of O(n^2).
  Matrix pivote_max() const;

  // turn the current matrix into upper triangular.
  // This operation have a complexity of O(n^3).
  Matrix upper_triangular() const;

  Vector operator*(const Vector &) const;
};
}; // namespace Algebra

#endif
