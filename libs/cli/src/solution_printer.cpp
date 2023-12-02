#include "cli/include/solution_printer.hpp"
#include <iomanip>
#include <ios>
#include <ostream>

void Cli::SolutionPrinter::print_system(const Algebra::Matrix &A,
                                        const Algebra::Vector &b,
                                        std::ostream &output) {
  int maxLength = 1;
  for (size_t i = 0; i < A.getSize(); i++) {
    for (size_t j = 0; j < A.getSize(); j++) {
      double number = A.getValue(i, j);
      int length = std::to_string(number).length();
      if (length > maxLength) {
        maxLength = length;
      }
    }
  }
  output << std::fixed << std::setprecision(3);
  for (size_t i = 0; i < A.getSize(); i++) {
    output << "|";
    for (size_t j = 0; j < A.getSize(); j++) {
      double value = A.getValue(i, j);
      output << std::setw(maxLength) << std::right << value;
    }
    double value = b.getValue(i);
    output << "| " << std::setw(maxLength) << value << "|" << std::left
           << std::endl;
  }
}
