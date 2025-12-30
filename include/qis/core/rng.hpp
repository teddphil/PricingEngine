#pragma once
#include <random>
#include "types.hpp"

namespace qis {

class Rng {
public:
  explicit Rng(std::uint64_t seed = 42) : eng_(seed), nd_(0.0, 1.0) {}
  Real normal() { return nd_(eng_); }

private:
  std::mt19937_64 eng_;
  std::normal_distribution<Real> nd_;
};

} // namespace qis
