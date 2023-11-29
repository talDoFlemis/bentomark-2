#include "inspector/include/validator.hpp"

std::vector<std::string> Inspector::Validator::get_error_messages() const {
  return this->error_messages;
}

void Inspector::Validator::clear_error_messages() {
  this->error_messages.clear();
  this->error_messages.shrink_to_fit();
}

void Inspector::Validator::add_constraint(std::function<void()> constraint) {
  this->constraints.emplace_back(constraint);
}

void Inspector::Validator::clear_constraints() {
  this->constraints.clear();
  this->constraints.shrink_to_fit();
}
