#pragma once
#include "qis/core/types.hpp"
#include "qis/core/timegrid.hpp"

namespace qis {

struct ModelState {
  Real spot{};
};

class Model {
public:
  virtual ~Model() = default;

  // evolve one step: given state at time t, return state at time t_next
  virtual ModelState evolve(Real t, Real t_next, const ModelState& x, Real z) const = 0;
};

} // namespace qis
