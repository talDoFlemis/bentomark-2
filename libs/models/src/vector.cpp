#include "models/include/vector.hpp"
#include <iostream>

Vector::Vector(int size) {
  this->size = size;
  this->values = (double *)malloc(sizeof(double) * size);
}

int Vector::getSize() { return this->size; }

void Vector::setValue(int i, double value) { this->values[i] = value; }

double Vector::getValue(int i) { return this->values[i]; }

void Vector::printVector() {
  for (int i = 0; i < this->size; i++) {
    std::cout << this->values[i] << " ";
  }
  std::cout << std::endl;
}

Vector Vector::operator+(Vector vec) {
  Vector vec2(this->size);

  for (int i = 0; i < this->size; i++) {
    vec2.setValue(i, this->getValue(i) + vec.getValue(i));
  }

  return vec2;
}

void Vector::operator<<(Vector vec) {
  for (int i = 0; i < this->size; i++) {
    this->setValue(i, vec.getValue(i));
  }
}