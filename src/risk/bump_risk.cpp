#include "qis/risk/bump_risk.hpp"

namespace qis {

BumpRiskResult BumpRisk::delta_bump(const McPricer& pricer, const TimeGrid& grid,
                                   Real s0, const Payoff& payoff,
                                   std::size_t n_paths, Real ds_rel) {
  auto base = pricer.price(grid, s0, payoff, n_paths, 777);
  Real ds = s0 * ds_rel;

  auto up   = pricer.price(grid, s0 + ds, payoff, n_paths, 777);
  auto down = pricer.price(grid, s0 - ds, payoff, n_paths, 777);

  Real delta = (up.pv - down.pv) / (2.0 * ds);
  return BumpRiskResult{ base.pv, delta, 0.0 };
}

} // namespace qis
