#pragma once
#include <cstddef>
#include "qis/core/types.hpp"
#include "qis/pricing/mc_pricer.hpp"
#include "qis/product/payoff.hpp"
#include "qis/core/timegrid.hpp"

namespace qis {

struct BumpRiskResult {
  Real pv{};
  Real delta{};
  Real vega{};
};

class BumpRisk {
public:
  // For demo: delta bumps s0; vega implemented by rebuilding model/sim in app layer.
  static BumpRiskResult delta_bump(const McPricer& pricer, const TimeGrid& grid,
                                  Real s0, const Payoff& payoff,
                                  std::size_t n_paths, Real ds_rel = 1e-4);
};

} // namespace qis
