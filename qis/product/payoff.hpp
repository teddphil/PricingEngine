#pragma once
#include "qis/core/types.hpp"
#include "qis/engine/index_simulator.hpp"

namespace qis {

class Payoff {
public:
  virtual ~Payoff() = default;
  virtual Real operator()(const Path& path) const = 0;
};

} // namespace qis
