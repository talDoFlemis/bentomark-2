#include "inputs/include/vector.hpp"
#include "cli/include/error_printer.hpp"
#include "inspector/include/number_validator.hpp"

Inputs::Vector::Vector(size_t size) : size(size) {}

Algebra::Vector Inputs::Vector::read(std::istream &input, std::ostream &output,
                                     std::ostream &error) {

  Algebra::Vector vector(size);
  output << "Digite os valores do vetor de tamanho " << size << std::endl;

  for (int i = 0; i < size; i++) {
    double value =
        Inputs::Vector::get_input_until_success(input, output, error, i);
    vector.setValue(i, value);
  }

  return vector;
}

double Inputs::Vector::get_input_until_success(std::istream &input,
                                               std::ostream &output,
                                               std::ostream &error,
                                               size_t i) const {

  std::string input_value;
  auto input_validator = Inspector::NumberValidator<double>("");

  while (true) {
    output << "Insira o valor da posição [" << i << "]: ";

    input_value.clear();
    std::getline(input, input_value);
    input_validator.set_value(input_value.c_str());

    if (input_validator.validate()) {
      break;
    }
    Cli::ErrorPrinter::error_list(error, input_validator.get_error_messages());
  }

  return input_validator.get_value();
}
