#include "inspector/include/number_validator.hpp"
#include <charconv>
#include <iostream>
#include <stdexcept>
#include <string>

template <typename T>
Inspector::NumberValidator<T>::NumberValidator(const std::string &target) {
  this->validate_value(target);
}

template <typename T>
Inspector::NumberValidator<T> &Inspector::NumberValidator<T>::between(T min,
                                                                      T max) {
  this->add_constraint([this, min, max]() {
    if (this->value < min || this->value > max) {
      this->error_messages.emplace_back("Valor não está entre " +
                                        std::to_string(min) + " e " +
                                        std::to_string(max));
    }
  });
  return *this;
}

template <typename T>
Inspector::NumberValidator<T> &
Inspector::NumberValidator<T>::greaterThan(T min) {
  this->add_constraint([this, min]() {
    if (this->value <= min) {
      this->error_messages.emplace_back("Valor não é maior que " +
                                        std::to_string(min));
    }
  });
  return *this;
}

template <typename T>
Inspector::NumberValidator<T> &Inspector::NumberValidator<T>::lessThan(T max) {
  this->add_constraint([this, max]() {
    if (this->value >= max) {
      this->error_messages.emplace_back("Valor não é menor que " +
                                        std::to_string(max));
    }
  });
  return *this;
}

template <typename T>
Inspector::NumberValidator<T> &Inspector::NumberValidator<T>::equal(T target) {
  this->add_constraint([this, target]() {
    if (this->value != target) {
      this->error_messages.emplace_back("Valor não é igual a " +
                                        std::to_string(target));
    }
  });
  return *this;
}

template <typename T>
Inspector::NumberValidator<T> &
Inspector::NumberValidator<T>::not_equal(T target) {
  this->add_constraint([this, target]() {
    if (this->value == target) {
      this->error_messages.emplace_back("Valor é igual a " +
                                        std::to_string(target));
    }
  });
  return *this;
}

template <typename T> bool Inspector::NumberValidator<T>::validate() {
  for (auto &constraint : this->constraints) {
    constraint();
  }
  if (!this->error_messages.empty()) {
    return false;
  }
  return true;
}

template <typename T> T Inspector::NumberValidator<T>::get_value() const {
  return this->value;
}

template <typename T>
void Inspector::NumberValidator<T>::set_value(const std::string &target) {
  this->clear_error_messages();
  this->validate_value(target);
}

template <typename T>
void Inspector::NumberValidator<T>::validate_value(const std::string &target) {

  if (target.empty()) {
    this->error_messages.emplace_back("Valor não pode ser vazio");
  }
  const auto finish = &*cend(target);
  const auto length = std::from_chars(&*cbegin(target), finish, this->value);
  if (length.ptr != finish) {
    this->error_messages.emplace_back("Não é um número válido");
  }
}

template class Inspector::NumberValidator<int>;
template class Inspector::NumberValidator<size_t>;
template class Inspector::NumberValidator<float>;
template class Inspector::NumberValidator<double>;

