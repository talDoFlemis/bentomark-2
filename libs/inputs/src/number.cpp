#include "inputs/include/number.hpp"
#include "cli/include/error_printer.hpp"

template <typename T>
Inputs::Number<T>::Number(Inspector::NumberValidator<T> *validator,
                          const std::string &message)
    : validator(validator), message(message) {}

template <typename T>
T Inputs::Number<T>::read(std::istream &in, std::ostream &out,
                          std::ostream &err) {
  std::string input_value;
  validator->clear_error_messages();

  while (true) {
    out << message;
    input_value.clear();
    std::getline(in, input_value);
    validator->set_value(input_value.c_str());
    if (validator->validate()) {
      break;
    }
    Cli::ErrorPrinter::error_list(err, validator->get_error_messages());
  }
  return validator->get_value();
}

template class Inputs::Number<int>;
template class Inputs::Number<size_t>;
template class Inputs::Number<float>;
template class Inputs::Number<double>;
