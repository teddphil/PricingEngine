#include "qis/engine/index_simulator.hpp"
#include "qis/core/rng.hpp"

namespace qis {

Path IndexSimulator::simulate(const TimeGrid& grid, Real s0, std::uint64_t seed) const {
  Rng rng(seed);

  ModelState x{ s0 };
  StrategyState st; // index starts at 100
  Path path;
  path.times = grid.times();
  path.index.resize(grid.size());
  path.spot.resize(grid.size());

  path.index[0] = st.index_level;
  path.spot[0]  = x.spot;

  for (std::size_t i = 0; i + 1 < grid.size(); ++i) {
    Real t  = grid[i];
    Real tn = grid[i + 1];

    // rebalance at time t
    strategy_.rebalance(t, st, x.spot);

    // evolve risky
    Real z = rng.normal();
    ModelState x_next = model_.evolve(t, tn, x, z);

    // apply index step
    strategy_.apply_step(t, tn, st, x.spot, x_next.spot, cash_.rate(t));

    x = x_next;
    path.spot[i + 1]  = x.spot;
    path.index[i + 1] = st.index_level;
  }

  return path;
}

} // namespace qis
