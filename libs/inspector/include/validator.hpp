#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <functional>
#include <string>
#include <vector>

namespace Inspector {
class Validator {
public:
  std::vector<std::string> error_messages;
  std::vector<std::function<void()>> constraints;

  // constructors
  Validator() = default;
  virtual ~Validator() = default;

  // methods
  virtual bool validate() = 0;
  std::vector<std::string> get_error_messages() const;
  void clear_error_messages();
  void add_constraint(std::function<void()>);
  void clear_constraints();
};
} // namespace Inspector

#endif // !VALIDATOR_H
