#include "algebra/include/matrix.hpp"
#include "algebra/include/vector.hpp"
#include "cli/include/solution_printer.hpp"
#include "inputs/include/matrix.hpp"
#include "inputs/include/number.hpp"
#include "inputs/include/vector.hpp"
#include "models/include/gauss_jacobi.hpp"
#include "models/include/model.hpp"
#include <cstddef>
#include <iostream>
#include <memory>
#include <vector>

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

    std::vector<std::unique_ptr<Models::Model>> models;
  }



  auto vectorsJacobi = std::vector<Algebra::Vector>();
  auto vectorsSeidel = std::vector<Algebra::Vector>();
  for (auto i = 0; i < n_systems; i++) {
    
    Models::GaussJacobi gaussJacobi;
    Models::GaussJacobi gaussSeidel;
      gaussJacobi.solve(matrices[i], vectors[i], epsilon, 1000);
      gaussSeidel.solve(matrices[i], vectors[i], epsilon, 1000);

      vectorsJacobi.emplace_back(gaussJacobi.getResult());
      vectorsSeidel.emplace_back(gaussSeidel.getResult());
    }

    for (auto i = 0; i < n_systems; i++) {

      Cli::SolutionPrinter::print_system(matrices[i], vectors[i], vectorsJacobi[i], std::cout);
      Cli::SolutionPrinter::print_system(matrices[i], vectors[i], vectorsSeidel[i], std::cout);
    }

  return 0;
}

