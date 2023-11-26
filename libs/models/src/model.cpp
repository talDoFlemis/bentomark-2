#include "models/include/model.hpp"
#include <cmath>
using namespace Models;

Algebra::Vector Model::getResult() const { return this->result.front(); }

double Model::getError(const Algebra::Vector &vec1,
                       const Algebra::Vector &vec2) const {
  size_t size = vec1.getSize();

  double max = 0;
  double current;
  for (int i = 0; i < size; i++) {
    current = std::abs(vec1.getValue(i) - vec2.getValue(i));
    if (current > max) {
      max = current;
    }
  }

  return max;
}
