#ifndef Matrix_H
#define Matrix_H

#include "algebra/include/vector.hpp"
#include <cstddef>
#include <initializer_list>
#include <ostream>
#include <sstream>
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

  Vector operator*(const Vector &) const;
};
std::ostream &operator<<(std::ostream &os, const Matrix &matrix);


}; // namespace Algebra

#endif
