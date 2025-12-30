#pragma once
#include "qis/core/types.hpp"

namespace qis {

class FlatCurve {
public:
  explicit FlatCurve(Real rate) : r_(rate) {}
  Real rate(Real /*t*/) const { return r_; }
  Real df(Real t) const { return std::exp(-r_ * t); }

private:
  Real r_;
};

} // namespace qis
