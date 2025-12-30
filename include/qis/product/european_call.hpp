#pragma once
#include <algorithm>
#include "payoff.hpp"

namespace qis {

class EuropeanCall final : public Payoff {
public:
  explicit EuropeanCall(Real strike) : k_(strike) {}
  Real operator()(const Path& path) const override {
    Real st = path.index.back();
    return std::max(st - k_, Real(0.0));
  }
private:
  Real k_;
};

} // namespace qis
