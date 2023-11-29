#ifndef MATRIX_INPUT_HPP
#define MATRIX_INPUT_HPP

#include "algebra/include/matrix.hpp"
#include "inputs/include/input.hpp"
#include <cstddef>
#include <istream>
#include <ostream>

namespace Inputs {
class Matrix : public Input<Algebra::Matrix> {
private:
  size_t size;
  double get_input_until_success(std::istream &, std::ostream &, std::ostream &,
                                 size_t, size_t) const;

public:
  explicit Matrix(size_t size);
  Algebra::Matrix read(std::istream &, std::ostream &, std::ostream &) override;
};

template class Input<Matrix>;
} // namespace Inputs

#endif // !MATRIX_INPUT_HPP
