#include "models/include/model.hpp"
#include <cmath>

Vector Model::getResult() { return *(this->result); }

double Model::getError(Vector vec1, Vector vec2) {
  int size = vec1.getSize();

  double max = 0, current;
  for (int i = 0; i < size; i++) {
    current = std::abs(vec1.getValue(i) - vec2.getValue(i));
    if (current > max) {
      max = current;
    }
  }

  return max;
}