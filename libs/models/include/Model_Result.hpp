#ifndef Model_Result_HPP
#define Model_Result_HPP

#include "algebra/include/vector.hpp"
#include <cstddef>
#include <vector>

namespace Models {
class Model_Result {
public:
  std::size_t s;
  std::vector<std::size_t> steps;
  std::vector<double> errors;
  std::vector<Algebra::Vector> xs;
  Model_Result();
  size_t next_step();
};
}; // namespace Models

#endif
