#include "algebra/include/matrix.hpp"
#include "cli/include/solution_printer.hpp"
#include "inputs/include/matrix.hpp"
#include "inputs/include/number.hpp"
#include "inputs/include/vector.hpp"
#include <cstddef>
#include <iostream>

int main(int argc, char *argv[]) {
  std::cout << "Digite a quantidade de sistemas que você deseja resolver: ";
  auto sys_valid = Inspector::NumberValidator<size_t>("").greaterThan(0);
  size_t n_systems =
      Inputs::Number<size_t>(sys_valid).read(std::cin, std::cout, std::cerr);

  auto matrices = std::vector<Algebra::Matrix>();
  auto vectors = std::vector<Algebra::Vector>();
  auto greater_than_zero =
      Inspector::NumberValidator<size_t>("").greaterThan(0);

  std::cout << "Digite o valor do epsilon: ";
  auto valid_epsilon = Inspector::NumberValidator<double>("").greaterThan(0);
  double epsilon = Inputs::Number<double>(valid_epsilon)
                       .read(std::cin, std::cout, std::cerr);

  std::cout << "Pegando as matrizes e os vetores" << std::endl;
  for (size_t i = 0; i < n_systems; i++) {
    std::cout << "Digite o tamanho da matriz: ";

    size_t matrix_size = Inputs::Number<size_t>(greater_than_zero)
                             .read(std::cin, std::cout, std::cerr);
    auto matrix = Inputs::Matrix(matrix_size);
    Algebra::Matrix m = matrix.read(std::cin, std::cout, std::cerr);
    matrices.emplace_back(m);

    auto vector = Inputs::Vector(matrix_size);
    Algebra::Vector v = vector.read(std::cin, std::cout, std::cerr);
    vectors.emplace_back(v);

    Cli::SolutionPrinter::print_system(m, v, std::cout);
  }

  for (auto &matrix : matrices) {
    matrix.printMatrix();
  }

  return 0;
}
