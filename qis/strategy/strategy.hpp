#pragma once
#include "qis/core/types.hpp"

namespace qis {

struct StrategyState {
  Real index_level{100.0};
  Real weight_risky{1.0};   // exposure to risky asset
  Real weight_cash{0.0};    // residual to cash
  Real realized_var{0.0};   // running variance estimate (toy)
};

class Strategy {
public:
  virtual ~Strategy() = default;

  // Called at each rebalance time to set weights.
  virtual void rebalance(Real t, StrategyState& st, Real risky_spot) const = 0;

  // Apply index update from asset return and cash accrual.
  virtual void apply_step(Real t, Real t_next, StrategyState& st,
                          Real risky_spot, Real risky_spot_next,
                          Real cash_rate) const = 0;
};

} // namespace qis
