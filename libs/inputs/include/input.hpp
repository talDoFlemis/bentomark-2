#ifndef INPUT_HPP
#define INPUT_HPP

#include <istream>

namespace Inputs {
template <typename T> class Input {
public:
  virtual ~Input() = default;
  virtual T read(std::istream &, std::ostream &, std::ostream &) = 0;
};
} // namespace Inputs

#endif // !INPUT_HPP
