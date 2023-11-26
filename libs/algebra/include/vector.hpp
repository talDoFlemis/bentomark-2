#ifndef Vector_H
#define Vector_H

#include <cstddef>
#include <initializer_list>
#include <ostream>
#include <vector>

namespace Algebra {
class Vector {
private:
  size_t size;
  std::vector<double> values;

public:
  explicit Vector(size_t);
  explicit Vector(std::initializer_list<double> &&);

  size_t getSize() const;
  void setValue(size_t, double);
  double getValue(size_t) const;
  void printVector();

  Vector operator+(const Vector &) const;
  void operator<<(const Vector &);
};

std::ostream &operator<<(std::ostream &, const Vector &);
}; // namespace Algebra

#endif
