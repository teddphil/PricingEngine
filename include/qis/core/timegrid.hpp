#pragma once
#include <vector>
#include "types.hpp"
#include "exceptions.hpp"

namespace qis {

// Simple year-fraction grid (ACT/365-ish for demo).
class TimeGrid {
public:
  static TimeGrid uniform(Real t0, Real t1, std::size_t steps) {
    if (steps == 0) throw QisError("TimeGrid: steps must be > 0");
    if (!(t1 > t0)) throw QisError("TimeGrid: require t1 > t0");
    TimeGrid g;
    g.times_.reserve(steps + 1);
    Real dt = (t1 - t0) / static_cast<Real>(steps);
    for (std::size_t i = 0; i <= steps; ++i) g.times_.push_back(t0 + dt * static_cast<Real>(i));
    return g;
  }

  const std::vector<Real>& times() const { return times_; }
  std::size_t size() const { return times_.size(); }
  Real operator[](std::size_t i) const { return times_.at(i); }

private:
  std::vector<Real> times_;
};

} // namespace qis
