#include <iostream>

#include "qis/core/timegrid.hpp"
#include "qis/market/flat_curve.hpp"
#include "qis/market/flat_vol.hpp"
#include "qis/model/gbm_model.hpp"
#include "qis/strategy/vol_target_strategy.hpp"
#include "qis/engine/index_simulator.hpp"
#include "qis/product/european_call.hpp"
#include "qis/pricing/mc_pricer.hpp"
#include "qis/risk/bump_risk.hpp"

int main() {
  using namespace qis;

  // Market
  Real s0 = 100.0;
  FlatCurve r(0.03);
  FlatCurve q(0.00);
  FlatVol vol(0.20);

  // Model + Strategy
  GbmModel model(r, q, vol);

  VolTargetParams vp;
  vp.target_vol = 0.10;
  vp.max_leverage = 2.0;
  vp.ewma_lambda = 0.94;
  VolTargetStrategy strategy(vp);

  // Simulator + Pricer
  IndexSimulator sim(model, strategy, r);
  McPricer pricer(sim, r);

  // Product: call on terminal index level
  EuropeanCall call(/*strike=*/100.0);

  // Time grid: 1Y, daily steps ~ 252
  auto grid = TimeGrid::uniform(0.0, 1.0, 252);

  std::size_t n_paths = 20000;
  auto res = pricer.price(grid, s0, call, n_paths, 123);

  std::cout << "PV: " << res.pv << "\n";
  std::cout << "StdErr: " << res.stderr << "\n";

  auto risk = BumpRisk::delta_bump(pricer, grid, s0, call, n_paths);
  std::cout << "Delta: " << risk.delta << "\n";

  return 0;
}
