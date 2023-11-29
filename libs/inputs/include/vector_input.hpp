#ifndef VECTOR_INPUT_HPP
#define VECTOR_INPUT_HPP

#include "algebra/include/vector.hpp"
#include "inputs/include/input.hpp"
#include <cstddef>
#include <istream>
#include <ostream>

namespace Inputs {
class Vector : public Input<Algebra::Vector> {
private:
  size_t size;
  double get_input_until_success(std::istream &, std::ostream &, std::ostream &,
                                 size_t) const;

public:
  explicit Vector(size_t size);
  Algebra::Vector read(std::istream &, std::ostream &, std::ostream &) override;
};

template class Input<Vector>;
} // namespace Inputs

#endif // !VECTOR_INPUT_HPP
