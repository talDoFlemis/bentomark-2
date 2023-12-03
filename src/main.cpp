#include "algebra/include/matrix.hpp"
#include "algebra/include/vector.hpp"
#include "cli/include/solution_printer.hpp"
#include "inputs/include/matrix.hpp"
#include "inputs/include/number.hpp"
#include "inputs/include/vector.hpp"
#include "models/include/gauss_jacobi.hpp"
#include "models/include/gauss_seidel.hpp"
#include "models/include/model.hpp"
#include <cstddef>
#include <iostream>
#include <memory>
#include <ostream>
#include <random>
#include <vector>

int main(int argc, char *argv[]) {

  std::cout << ".______    _______ .__   __. .___________.  ______      ___    "
               " ______  .___  ___.      ___      .______       __  ___"
            << std::endl;
  std::cout << "|   _  \\  |   ____||  \\ |  | |           | /  __  \\    /  / "
               "   /  /\\  \\ |   \\/   |     /   \\     |   _  \\     |  |/  /"
            << std::endl;
  std::cout << "|  |_)  | |  |__   |   \\|  | `---|  |----`|  |  |  |  /  /    "
               "/  /  \\  \\|  \\  /  |    /  ^  \\    |  |_)  |    |  '  /"
            << std::endl;
  std::cout << "|   _  <  |   __|  |  . `  |     |  |     |  |  |  | <  <    / "
               " /    >  >  |\\/|  |   /  /_\\  \\   |      /     |    <"
            << std::endl;
  std::cout << "|  |_)  | |  |____ |  |\\   |     |  |     |  `--'  |  \\  \\  "
               "/  /    /  /|  |  |  |  /  _____  \\  |  |\\  \\----.|  .  \\"
            << std::endl;
  std::cout
      << "|______/  |_______||__| \\__|     |__|      \\______/    \\__\\/__/  "
         "  /__/ |__|  |__| /__/     \\__\\ | _| `._____||__|\\__\\"
      << std::endl;

  std::cout << std::endl;
  std::cout << std::endl;

  auto greater_than_zero = Inspector::NumberValidator<size_t>("0");
  greater_than_zero.greaterThan(0);
  size_t n_systems =
      Inputs::Number<size_t>(
          &greater_than_zero,
          "Digite a quantidade de sistemas que você deseja resolver: ")
          .read(std::cin, std::cout, std::cerr);
  auto matrices = std::vector<Algebra::Matrix>();
  auto pivoteds = std::vector<Algebra::Matrix>();
  auto vectors = std::vector<Algebra::Vector>();

  // auto valid_epsilon = Inspector::NumberValidator<double>("");
  // valid_epsilon.greaterThan(0);
  // double epsilon =
  //     Inputs::Number<double>(&valid_epsilon, "Digite o valor do epsilon: ")
  //         .read(std::cin, std::cout, std::cerr);

  // std::cout << "Pegando as matrizes e os vetores" << std::endl;
  // for (size_t i = 0; i < n_systems; i++) {
  //   size_t matrix_size = Inputs::Number<size_t>(&greater_than_zero,
  //                                               "Digite o tamanho da matriz:
  //                                               ")
  //                            .read(std::cin, std::cout, std::cerr);
  //   auto matrix = Inputs::Matrix(matrix_size);
  //   Algebra::Matrix m = matrix.read(std::cin, std::cout, std::cerr);
  //   matrices.emplace_back(m);

  //   auto vector = Inputs::Vector(matrix_size);
  //   Algebra::Vector v = vector.read(std::cin, std::cout, std::cerr);
  //   vectors.emplace_back(v);

  //   std::vector<std::unique_ptr<Models::Model>> models;
  // }

  matrices.emplace_back(Algebra::Matrix{{{10, 2, 1}, {1, 5, 1}, {2, 3, 10}}});
  vectors.emplace_back(Algebra::Vector{7, -8, 6});
  pivoteds.emplace_back(matrices[0].pivote_max());

  matrices.emplace_back(Algebra::Matrix{{{5, 3, 1}, {5, 6, 1}, {1, 6, 7}}});
  vectors.emplace_back(Algebra::Vector{1, 2, 3});
  pivoteds.emplace_back(matrices[1].pivote_max());

  matrices.emplace_back(Algebra::Matrix{{{2, 3, 10}, {10, 2, 1}, {1, 5, 1}}});
  vectors.emplace_back(Algebra::Vector{7, -8, 6});
  pivoteds.emplace_back(matrices[2].pivote_max());

  auto vectorsJacobi = std::vector<Algebra::Vector>();
  auto vectorsSeidel = std::vector<Algebra::Vector>();
  for (auto i = 0; i < n_systems; i++) {

    Models::GaussJacobi gaussJacobi;
    Models::GaussSeidel gaussSeidel;

    if (matrices[i].checkLineCriteria()) {
      gaussJacobi.solve(matrices[i], vectors[i], 0.01, 1000);
      gaussSeidel.solve(matrices[i], vectors[i], 0.01, 1000);
    } else {
      gaussJacobi.solve(pivoteds[i], vectors[i], 0.01, 1000);
      gaussSeidel.solve(pivoteds[i], vectors[i], 0.01, 1000);
    }

    vectorsJacobi.emplace_back(gaussJacobi.getResult());
    vectorsSeidel.emplace_back(gaussSeidel.getResult());
  }

  for (auto i = 0; i < n_systems; i++) {
    std::cout << "Resolvendo o sistema " << i + 1<< ":" << std::endl;
    
    std::cout << "Matriz Inversa: " << std::endl;
    std::cout <<matrices[i] << std::endl;
    

    std::cout << "Solução por Gauss-Jacobi: " << std::endl;
    Cli::SolutionPrinter::print_system(matrices[i], vectors[i],
                                       vectorsJacobi[i], std::cout);
    std::cout << "Solução por Gauss-Seidel: " << std::endl;
    Cli::SolutionPrinter::print_system(matrices[i], vectors[i],
                                       vectorsSeidel[i], std::cout);
  }
}
