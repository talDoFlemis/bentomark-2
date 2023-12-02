#include "algebra/include/matrix.hpp"
#include <cstddef>
#include <iostream>

using namespace Algebra;

Matrix::Matrix(size_t size)
    : size{size}, values{std::vector<double>(size * size, 0.0)} {}

size_t Matrix::getSize() const { return this->size; }

void Matrix::setValue(size_t i, size_t j, double value) {
  this->values[i * this->size + j] = value;
}

double Matrix::getValue(size_t i, size_t j) const {
  return this->values[i * this->size + j];
}

void Matrix::printMatrix() {
  for (int i = 0; i < this->size; i++) {
    for (int j = 0; j < this->size; j++) {
      std::cout << this->values[i * this->size + j] << " ";
    }
    std::cout << std::endl;
  }
}

Vector Matrix::operator*(const Vector &vec) const {
  Vector result(this->size);
  double value;

  for (int i = 0; i < this->size; i++) {
    value = 0;
    for (int j = 0; j < this->size; j++) {
      value += this->getValue(i, j) * vec.getValue(j);
    }
    result.setValue(i, value);
  }

  return result;
}

Matrix::Matrix(std::initializer_list<std::initializer_list<double>> &&list)
    : size{list.size()}, values{std::vector<double>(size * size, 1.0)} {
  int i = 0;
  int j = 0;
  auto rows = std::move(list);
  for (auto &row : rows) {
    for (auto &value : row) {
      this->setValue(i, j, value);
      j++;
    }
    i++;
    j = 0;
  }
}

Matrix Matrix::pivote_max() const {
  Algebra::Matrix m{size};

  for (size_t j = 0; j < size; ++j) {
    double max = getValue(j, j);
    double max_line = 0;
    for (size_t i = j + 1; i < size; ++i) {
      double v = getValue(i, j);
      if (v > max) {
        max = v;
        max_line = i;
      }
    }

    for (size_t k = 0; k < size; ++k) {
      m.setValue(j, k, getValue(max_line, k));
    }
  }
  return m;
}

Matrix Matrix::upper_triangular() const {
  Algebra::Matrix m{*this};

  // turns `m` into upper triangular
  for (size_t p = 0; p < size; ++p) {
    double pivot = getValue(p, p);
    for (size_t i = p + 1; i < size; ++i) {
      double x = getValue(i, p);
      if (x == 0) {
        continue;
      }

      for (size_t j = 0; j < size; ++j) {
        double new_val = m.getValue(i, j) - (getValue(p, j) * (x / pivot));
        m.setValue(i, j, new_val);
      }
    }
  }
  return m;
}
