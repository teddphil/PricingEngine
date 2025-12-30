#pragma once
#include "qis/core/types.hpp"

namespace qis {

class FlatVol {
public:
  explicit FlatVol(Real vol) : vol_(vol) {}
  Real sigma(Real /*t*/, Real /*s*/) const { return vol_; }

private:
  Real vol_;
};

} // namespace qis
