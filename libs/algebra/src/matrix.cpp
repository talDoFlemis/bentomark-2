#include "algebra/include/matrix.hpp"
#include <cstddef>
#include <iomanip>
#include <ios>
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

std::ostream &Algebra::operator<<(std::ostream &os, const Matrix &matrix) {
  int maxLength = 1;
  for (size_t i = 0; i < matrix.getSize(); i++) {
    for (size_t j = 0; j < matrix.getSize(); j++) {
      maxLength =
          std::max(maxLength,
                   static_cast<int>(std::to_string(matrix.getValue(i, j)).length()));
    }
  }

  os <<std::fixed << std::setprecision(3);
  for (int i = 0; i < matrix.getSize(); i++) {
    os << "|";
    for (int j = 0; j < matrix.getSize(); j++) {
      double number = matrix.getValue(i, j);

      os << std::setw(maxLength) << number << std::right;
    }
    os << "|" << std::endl;
  }
  return os;
}
