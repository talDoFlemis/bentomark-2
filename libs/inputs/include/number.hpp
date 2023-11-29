#ifndef NUMBER_INPUT_HPP
#define NUMBER_INPUT_HPP

#include "inputs/include/input.hpp"
#include "inspector/include/number_validator.hpp"
namespace Inputs {
template <typename T> class Number : public Input<T> {
private:
  Inspector::NumberValidator<T> validator;

public:
  explicit Number(Inspector::NumberValidator<T>);
  T read(std::istream &, std::ostream &, std::ostream &) override;
};

template class Number<int>;
template class Number<size_t>;
template class Number<float>;
template class Number<double>;
};     // namespace Inputs
#endif // !NUMBER_INPUT_HPP
