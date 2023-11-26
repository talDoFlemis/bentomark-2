#include "models/include/vector.hpp"
#include <cstddef>
#include <iostream>

using namespace Models;

Vector::Vector(size_t size)
    : size{size}, values{std::vector<double>(size, 0.0)} {}

Vector::Vector(std::initializer_list<double> &&list)
    : size{list.size()}, values{std::vector<double>(size, 0.0)} {
  int i = 0;
  auto items = std::move(list);
  for (auto &value : items) {
    this->setValue(i, value);
    i++;
  }
}

size_t Vector::getSize() const { return this->size; }

void Vector::setValue(size_t i, double value) { this->values[i] = value; }

double Vector::getValue(size_t i) const { return this->values[i]; }

void Vector::printVector() {
  for (int i = 0; i < this->size; i++) {
    std::cout << this->values[i] << " ";
  }
  std::cout << std::endl;
}

Vector Vector::operator+(const Vector &vec) const {
  Vector vec2(this->size);

  for (int i = 0; i < this->size; i++) {
    vec2.setValue(i, this->getValue(i) + vec.getValue(i));
  }

  return vec2;
}

void Vector::operator<<(const Vector &vec) {
  for (int i = 0; i < this->size; i++) {
    this->setValue(i, vec.getValue(i));
  }
}

std::ostream &operator<<(std::ostream &os, const Vector &vec) {
  os << "[ ";
  for (int i = 0; i < vec.getSize(); i++) {
    os << vec.getValue(i) << " ";
  }
  os << "]";
  return os;
}
