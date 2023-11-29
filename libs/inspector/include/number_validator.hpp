#ifndef NUMBER_H
#define NUMBER_H

#include "inspector/include/validator.hpp"
#include <string>

namespace Inspector {
template <typename T> class NumberValidator : public Validator {
private:
  T value;

public:
  explicit NumberValidator(const std::string &);
  NumberValidator &between(T min, T max);
  NumberValidator &greaterThan(T min);
  NumberValidator &lessThan(T max);
  NumberValidator &equal(T value);
  NumberValidator &not_equal(T value);
  bool validate() override;
  T get_value() const;
  void set_value(const std::string &);
};

template class NumberValidator<int>;
template class NumberValidator<float>;
} // namespace Inspector

#endif // !NUMBER_H
