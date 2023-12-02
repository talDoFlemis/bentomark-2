#ifndef SOLUTION_PRINT_HPP
#define SOLUTION_PRINT_HPP

#include "algebra/include/matrix.hpp"
#include "algebra/include/vector.hpp"

namespace Cli {
class SolutionPrinter {
public:
  static void print_system(const Algebra::Matrix &, const Algebra::Vector &,
                           std::ostream &output);
};
};     // namespace Cli
#endif // !SOLUTION_PRINT_HPP
