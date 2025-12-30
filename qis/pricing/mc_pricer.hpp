#pragma once
#include <cstddef>
#include "qis/core/types.hpp"
#include "qis/core/timegrid.hpp"
#include "qis/engine/index_simulator.hpp"
#include "qis/product/payoff.hpp"
#include "qis/market/flat_curve.hpp"

namespace qis {

struct McResult {
  Real pv{};
  Real stderr{};
};

class McPricer {
public:
  McPricer(const IndexSimulator& sim, FlatCurve discount)
    : sim_(sim), disc_(discount) {}

  McResult price(const TimeGrid& grid, Real s0, const Payoff& payoff,
                 std::size_t n_paths, std::uint64_t seed0 = 1234) const;

private:
  const IndexSimulator& sim_;
  FlatCurve disc_;
};

} // namespace qis
