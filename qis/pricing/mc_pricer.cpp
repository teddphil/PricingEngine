#include "qis/pricing/mc_pricer.hpp"
#include <cmath>

namespace qis {

McResult McPricer::price(const TimeGrid& grid, Real s0, const Payoff& payoff,
                         std::size_t n_paths, std::uint64_t seed0) const {
  Real sum = 0.0;
  Real sum2 = 0.0;

  Real T = grid.times().back();
  Real df = disc_.df(T);

  for (std::size_t i = 0; i < n_paths; ++i) {
    Path path = sim_.simulate(grid, s0, seed0 + static_cast<std::uint64_t>(i));
    Real p = payoff(path);
    Real x = df * p;
    sum += x;
    sum2 += x * x;
  }

  Real mean = sum / static_cast<Real>(n_paths);
  Real var  = (sum2 / static_cast<Real>(n_paths)) - mean * mean;
  var = (var > 0.0 ? var : 0.0);

  Real stderr = std::sqrt(var / static_cast<Real>(n_paths));
  return McResult{ mean, stderr };
}

} // namespace qis
