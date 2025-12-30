#pragma once
#include <vector>
#include "qis/core/timegrid.hpp"
#include "qis/model/model.hpp"
#include "qis/strategy/strategy.hpp"
#include "qis/market/flat_curve.hpp"

namespace qis {

struct Path {
  std::vector<Real> times;
  std::vector<Real> index;
  std::vector<Real> spot;
};

class IndexSimulator {
public:
  IndexSimulator(const Model& model, const Strategy& strategy,
                 FlatCurve cash_curve)
    : model_(model), strategy_(strategy), cash_(cash_curve) {}

  Path simulate(const TimeGrid& grid, Real s0, std::uint64_t seed) const;

private:
  const Model& model_;
  const Strategy& strategy_;
  FlatCurve cash_;
};

} // namespace qis
