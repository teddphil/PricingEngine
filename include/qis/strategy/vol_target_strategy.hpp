#pragma once
#include <algorithm>
#include <cmath>
#include "strategy.hpp"

namespace qis {

struct VolTargetParams {
  Real target_vol{0.10};   // 10% annualized
  Real max_leverage{2.0};
  Real min_leverage{0.0};
  Real ewma_lambda{0.94};  // variance EWMA
  Real tc_bps{0.0};        // transaction cost in bps (simple)
};

class VolTargetStrategy final : public Strategy {
public:
  explicit VolTargetStrategy(VolTargetParams p) : p_(p) {}

  void rebalance(Real /*t*/, StrategyState& st, Real /*risky_spot*/) const override {
    // Convert variance to annualized vol estimate; guard small values.
    Real est_vol = std::sqrt(std::max(st.realized_var, Real(1e-12)));
    Real lev = p_.target_vol / est_vol;

    lev = std::clamp(lev, p_.min_leverage, p_.max_leverage);

    st.weight_risky = lev;
    st.weight_cash  = 1.0 - lev;
  }

  void apply_step(Real t, Real t_next, StrategyState& st,
                  Real risky_spot, Real risky_spot_next,
                  Real cash_rate) const override {
    Real dt = t_next - t;
    Real r_cash = cash_rate;

    // risky return
    Real ret_risky = (risky_spot_next / risky_spot) - 1.0;
    // cash return
    Real ret_cash  = std::exp(r_cash * dt) - 1.0;

    // transaction cost: penalize change in risky weight (toy model)
    // Here we assume weights were set at the beginning of the step.
    // In a richer model we'd keep previous weights and compute turnover.
    Real tc = (p_.tc_bps * 1e-4) * std::abs(st.weight_risky); // placeholder

    Real index_ret = st.weight_risky * ret_risky + st.weight_cash * ret_cash - tc;
    st.index_level *= (1.0 + index_ret);

    // EWMA variance update using log return approximation
    Real logret = std::log(std::max(1e-12, 1.0 + ret_risky));
    Real inst_var = (logret * logret) / std::max(dt, Real(1e-12)); // variance rate
    st.realized_var = p_.ewma_lambda * st.realized_var + (1.0 - p_.ewma_lambda) * inst_var;
  }

private:
  VolTargetParams p_;
};

} // namespace qis
