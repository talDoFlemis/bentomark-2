#include "cli/include/solution_printer.hpp"
#include <iomanip>
#include <ios>
#include <ostream>

void Cli::SolutionPrinter::print_system(const Algebra::Matrix &A,
                                        const Algebra::Vector &b,
                                        const Algebra::Vector &d,
                                        std::ostream &output) {
  int matrixLength = 1;
  for (size_t i = 0; i < A.getSize(); i++) {
    for (size_t j = 0; j < A.getSize(); j++) {
      double number = A.getValue(i, j);
      int length = std::to_string(number).length();
      if (length > matrixLength) {
        matrixLength = length;
      }
    }
  }
  int vectorLength = 1;
  for (size_t i = 0; i < d.getSize(); i++) {
    double number = d.getValue(i);
    int length = std::to_string(number).length();
    if (length > vectorLength) {
      vectorLength = length;
    }
  }
  output << std::fixed << std::setprecision(3);
  for (size_t i = 0; i < A.getSize(); i++) {
    output << "|";
    for (size_t j = 0; j < A.getSize(); j++) {
      double value = A.getValue(i, j);
      output << std::setw(matrixLength) << std::right << value;
    }
    double valueB = b.getValue(i);
    double valueD = d.getValue(i);
    //print vector b
    output << "|" << std::setw(matrixLength) << valueB << "|" << std::right << ((i == 1) ? " = " : "   ");
    //print vector d
    output << "|"<<std::setw(vectorLength)<< std::right<<valueD << "|" << std::endl;
  }

  output << std::endl;

}
