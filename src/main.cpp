#include "algebra/include/matrix.hpp"
#include "cli/include/solution_printer.hpp"
#include "inputs/include/matrix.hpp"
#include "inputs/include/number.hpp"
#include "inputs/include/vector.hpp"
#include <cstddef>
#include <iostream>

int main(int argc, char *argv[]) {
  auto greater_than_zero = Inspector::NumberValidator<size_t>("0");
  greater_than_zero.greaterThan(0);
  size_t n_systems =
      Inputs::Number<size_t>(
          &greater_than_zero,
          "Digite a quantidade de sistemas que você deseja resolver: ")
          .read(std::cin, std::cout, std::cerr);
  auto matrices = std::vector<Algebra::Matrix>();
  auto vectors = std::vector<Algebra::Vector>();

  auto valid_epsilon = Inspector::NumberValidator<double>("");
  valid_epsilon.greaterThan(0);
  double epsilon =
      Inputs::Number<double>(&valid_epsilon, "Digite o valor do epsilon: ")
          .read(std::cin, std::cout, std::cerr);

  std::cout << "Pegando as matrizes e os vetores" << std::endl;
  for (size_t i = 0; i < n_systems; i++) {
    size_t matrix_size = Inputs::Number<size_t>(&greater_than_zero,
                                                "Digite o tamanho da matriz: ")
                             .read(std::cin, std::cout, std::cerr);
    auto matrix = Inputs::Matrix(matrix_size);
    Algebra::Matrix m = matrix.read(std::cin, std::cout, std::cerr);
    matrices.emplace_back(m);

    auto vector = Inputs::Vector(matrix_size);
    Algebra::Vector v = vector.read(std::cin, std::cout, std::cerr);
    vectors.emplace_back(v);

    Cli::SolutionPrinter::print_system(m, v, std::cout);
  }

  for (const auto &matrix : matrices) {
    std::cout << matrix;
  }

  return 0;
}
