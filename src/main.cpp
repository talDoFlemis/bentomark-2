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
#include <iomanip>
#include <iostream>
#include <memory>
#include <ostream>
#include <random>
#include <vector>

int main(int argc, char *argv[]) {

   std::cout << std::setprecision(5);

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

   auto systemSize = Inspector::NumberValidator<size_t>("0");
   systemSize.greaterThan(0);

   std::cout << "\nBem vindo ao BENTOMARK 2.0!\nQual operação você deseja realizar?\n";
   std::cout << "[0] Resolver um sistema linear\n";
   std::cout << "[1] Achar a inversa de uma matriz\n";

  auto ternario = Inspector::NumberValidator<size_t>("0");
  ternario.between(0, 2);

  auto zero_or_one = Inspector::NumberValidator<size_t>("0");
  zero_or_one.between(0, 1);
  size_t systemOrInverse =
      Inputs::Number<size_t>(
          &zero_or_one,
          "Entre a opção desejada [0/1]: ")
          .read(std::cin, std::cout, std::cerr);
   
   auto greater_than_zero = Inspector::NumberValidator<size_t>("0");
   greater_than_zero.greaterThan(0);

   std::cout << std::endl;

   if (systemOrInverse == 0) {
      size_t newOrBenchmark =
      Inputs::Number<size_t>(
          &zero_or_one,
          "Deseja entrar um sistema customizado [0] ou usar o nosso benchmark [1]? : ")
          .read(std::cin, std::cout, std::cerr);


      if (newOrBenchmark == 1) {
         size_t n_systems =
               Inputs::Number<size_t>(
                  &greater_than_zero,
                  "Digite a quantidade de sistemas que você deseja resolver: ")
                  .read(std::cin, std::cout, std::cerr);
         auto matrices = std::vector<Algebra::Matrix>();
         auto pivoteds = std::vector<Algebra::Matrix>();
         auto vectors = std::vector<Algebra::Vector>();

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
            
            std::cout << "Solução por Gauss-Jacobi: " << std::endl;
            Cli::SolutionPrinter::print_system(matrices[i], vectors[i],
                                                vectorsJacobi[i], std::cout);
            std::cout << "Solução por Gauss-Seidel: " << std::endl;
            Cli::SolutionPrinter::print_system(matrices[i], vectors[i],
                                                vectorsSeidel[i], std::cout);
         }
      } else if (newOrBenchmark == 0) {
         size_t size =
         Inputs::Number<size_t>(
            &greater_than_zero,
            "Entre o tamanho do sistema: ")
            .read(std::cin, std::cout, std::cerr);
         
         Algebra::Matrix A(size);
         Algebra::Vector b(size);

         auto valid_epsilon = Inspector::NumberValidator<double>("");
         valid_epsilon.greaterThan(0);
         double epsilon =
            Inputs::Number<double>(&valid_epsilon, "Digite o valor do epsilon: ")
               .read(std::cin, std::cout, std::cerr);

         std::cout << std::endl;

         double aux;
         for (int i = 0; i < size; i++) {
            std::cout << "Entre o " << i << "-ésimo valor do vetor b: ";
            std::cin >> aux;
            b.setValue(i, aux);
         }
         std::cout << std::endl;
         for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
               std::cout << "Entre o elemento A" << i << "x" << j << ": ";
               std::cin >> aux;
               A.setValue(i, j, aux);
            }
         }

         std::cout << std::endl;

         size_t showSteps =
         Inputs::Number<size_t>(
            &zero_or_one,
            "Deseja visualizar todos os passos? [0/1]: ")
            .read(std::cin, std::cout, std::cerr);
         
         size_t jacobiSeidel =
         Inputs::Number<size_t>(
            &ternario,
            "Deseja utilizar o método de Gauss-Jacobi, Gauss-Seidel, ou ambos? [0/1/2]: ")
            .read(std::cin, std::cout, std::cerr);
         
         std::cout << std::endl;

         Models::GaussJacobi jacobi;
         Models::GaussSeidel seidel;
         Algebra::Vector jacobiResult(size);
         Algebra::Vector seidelResult(size);
         Algebra::Matrix A2(size);

         if (jacobiSeidel == 0 || jacobiSeidel == 2) {
            if (!A.checkLineCriteria()) {
               A2 = A.pivote_max();
               std::cout << A2 << std::endl;
               jacobi.solve(A2, b, epsilon, 100);
            } else {
               jacobi.solve(A, b, epsilon, 100);
            }
            jacobiResult << jacobi.getResult();
            std::cout << "Solução por Gauss-Jacobi:\n";
            std::cout << std::endl;
            if (showSteps == 1) {
               std::cout << "Passos:" << std::endl;
               std::cout << "| Erro | X" << std::endl;
               auto passos = jacobi.get_model_result();
               for (int i = 0; i < passos.s; i++) {
                  std::cout << "| " << passos.errors[i] << " |";
                  for (int j = 0; j < size; j++) {
                     std::cout << " " << passos.xs[i].getValue(j);
                  } std::cout << std::endl;
               }
            }
            std::cout << std::endl;
            Cli::SolutionPrinter::print_system(A, b, jacobiResult, std::cout);
         }
         if (jacobiSeidel == 1 || jacobiSeidel == 2) {
            if (!A.checkLineCriteria()) {
               A2 = A.pivote_max();
               seidel.solve(A2, b, epsilon, 100);
            } else {
               seidel.solve(A, b, epsilon, 100);
            }
            seidelResult << seidel.getResult();
            std::cout << "Solução por Gauss-Seidel:\n";
            std::cout << std::endl;
            if (showSteps == 1) {
               std::cout << "Passos:" << std::endl;
               std::cout << "| Erro | X" << std::endl;
               auto passos = seidel.get_model_result();
               for (int i = 0; i < passos.s; i++) {
                  std::cout << "| " << passos.errors[i] << " |";
                  for (int j = 0; j < size; j++) {
                     std::cout << " " << passos.xs[i].getValue(j);
                  } std::cout << std::endl;
               }
            }
            std::cout << std::endl;
            Cli::SolutionPrinter::print_system(A, b, seidelResult, std::cout);
         }  
      }
   } else if (systemOrInverse == 1) {
      size_t newOrBenchmark =
      Inputs::Number<size_t>(
          &zero_or_one,
          "Deseja entrar uma matriz customizada [0] ou usar o nosso benchmark [1]? : ")
          .read(std::cin, std::cout, std::cerr);
         
      
      if (newOrBenchmark == 1) {
         size_t n_systems =
               Inputs::Number<size_t>(
                  &greater_than_zero,
                  "Digite a quantidade de matrizes que você deseja resolver: ")
                  .read(std::cin, std::cout, std::cerr);
         auto matrices = std::vector<Algebra::Matrix>();

         matrices.emplace_back(Algebra::Matrix{{{10, 2, 1}, {1, 5, 1}, {2, 3, 10}}});

         matrices.emplace_back(Algebra::Matrix{{{5, 3, 1}, {5, 6, 1}, {1, 6, 7}}});

         matrices.emplace_back(Algebra::Matrix{{{2, 3, 10}, {10, 2, 1}, {1, 5, 1}}});

         auto vectorsJacobi = std::vector<Algebra::Matrix>();
         auto vectorsSeidel = std::vector<Algebra::Matrix>();
         for (auto i = 0; i < n_systems; i++) {

            Models::GaussJacobi gaussJacobi;
            Models::GaussSeidel gaussSeidel;

            vectorsJacobi.emplace_back(gaussJacobi.solveInverse(matrices[i], 1e-5, 100));
            vectorsSeidel.emplace_back(gaussSeidel.solveInverse(matrices[i], 1e-5, 100));
         }
         std::cout << std::endl;
         for (auto i = 0; i < n_systems; i++) {
            std::cout << "Resolvendo a inversa " << i + 1<< ":" << std::endl;
            
            std::cout << "Solução por Gauss-Jacobi: " << std::endl;
            std::cout << std::endl;
            std::cout << vectorsJacobi[i] << std::endl;
            std::cout << std::endl;
            std::cout << "Solução por Gauss-Seidel: " << std::endl;
            std::cout << std::endl;
            std::cout << vectorsSeidel[i] << std::endl;
            std::cout << std::endl;
         }
      } else if (newOrBenchmark == 0) {
         size_t size =
         Inputs::Number<size_t>(
            &greater_than_zero,
            "Entre o tamanho da matriz: ")
            .read(std::cin, std::cout, std::cerr);
         
         Algebra::Matrix A(size);

         auto valid_epsilon = Inspector::NumberValidator<double>("");
         valid_epsilon.greaterThan(0);
         double epsilon =
            Inputs::Number<double>(&valid_epsilon, "Digite o valor do epsilon: ")
               .read(std::cin, std::cout, std::cerr);

         std::cout << std::endl;

         double aux;
         std::cout << std::endl;
         for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
               std::cout << "Entre o elemento A" << i << "x" << j << ": ";
               std::cin >> aux;
               A.setValue(i, j, aux);
            }
         }

         std::cout << std::endl;
         
         size_t jacobiSeidel =
         Inputs::Number<size_t>(
            &ternario,
            "Deseja utilizar o método de Gauss-Jacobi, Gauss-Seidel, ou ambos? [0/1/2]: ")
            .read(std::cin, std::cout, std::cerr);
         
         std::cout << std::endl;

         Models::GaussJacobi jacobi;
         Models::GaussSeidel seidel;
         Algebra::Vector jacobiResult(size);
         Algebra::Vector seidelResult(size);
         Algebra::Matrix A2(size);

         if (jacobiSeidel == 0 || jacobiSeidel == 2) {
            std::cout << "Solução por Gauss-Jacobi:\n";
            std::cout << std::endl;
            std::cout << jacobi.solveInverse(A, epsilon, 100) << std::endl; 
            std::cout << std::endl;
         }
         if (jacobiSeidel == 1 || jacobiSeidel == 2) {
            std::cout << "Solução por Gauss-Seidel:\n";
            std::cout << std::endl;
            std::cout << seidel.solveInverse(A, epsilon, 100) << std::endl; 
            std::cout << std::endl;
         }
      }
   }
}
