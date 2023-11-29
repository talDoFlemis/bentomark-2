#include "inputs/include/matrix.hpp"
#include "inspector/include/number_validator.hpp"
#include <limits>

Inputs::Matrix::Matrix(size_t size) : size(size) {}

Algebra::Matrix Inputs::Matrix::read(std::istream &input, std::ostream &output,
                                     std::ostream &error) {
  Algebra::Matrix matrix(size);
  output << "Digite os valores da matriz " << size << " X " << size
         << std::endl;

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      double value =
          Inputs::Matrix::get_input_until_success(input, output, error, i, j);
      matrix.setValue(i, j, value);
    }
  }

  return matrix;
}

double Inputs::Matrix::get_input_until_success(std::istream &input,
                                               std::ostream &output,
                                               std::ostream &error, size_t i,
                                               size_t j) const {
  std::string input_value;
  auto input_validator = Inspector::NumberValidator<double>("");

  while (true) {
    output << "Insira o valor da posição [" << i << "][" << j << "]: ";

    input_value.clear();
    std::getline(input, input_value);
    input_validator.set_value(input_value.c_str());

    if (input_validator.validate()) {
      break;
    }
    error << "Valor inválido, tente novamente" << std::endl;
  }

  return input_validator.get_value();
}
