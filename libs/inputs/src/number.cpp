#include "inputs/include/number.hpp"

template <typename T>
Inputs::Number<T>::Number(Inspector::NumberValidator<T> validator)
    : validator(validator) {}

template <typename T>
T Inputs::Number<T>::read(std::istream &in, std::ostream &out,
                          std::ostream &err) {
  std::string input_value;
  validator.clear_error_messages();

  out << "Entre um número";

  while (true) {
    in >> input_value;
    validator.set_value(input_value.c_str());
    if (validator.validate()) {
      break;
    }
    err << "Número inválido" << std::endl;
  }
  return validator.get_value();
}
