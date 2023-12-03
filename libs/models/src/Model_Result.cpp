#include "models/include/Model_Result.hpp"

using namespace Models;

Model_Result::Model_Result()
    : s{0}, steps{std::vector<size_t>()}, xs{std::vector<Algebra::Vector>()},
      errors{std::vector<double>()} {}

size_t Model_Result::next_step() { return ++s; }
