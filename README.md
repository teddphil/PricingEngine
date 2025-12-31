# QIS Pricing Engine (C++)

A C++20 pricing and risk-management framework for Quantitative Investment Strategies (QIS) and derivatives written on dynamic investment strategy indices.

## Specific goals
- Simulate *rules-based investment strategies* (e.g. volatility targeting),
- Price *derivatives on strategy indices* via Monte Carlo, produce *risk sensitivities* in a clean, extensible design.

## Key Features

- Strategy & Index Modelling
  - Dynamic *volatility-targeting strategy*.
  - Discrete rebalancing with cash allocation.
  - Index construction driven by asset returns.
- Market & Models
  - Risk-neutral *Geometric Brownian Motion (GBM)*.
  - Flat interest rate, dividend yield, and volatility (for clarity).
  - Clean separation between *market data*, *model*, and *strategy*.
- Pricing
  - *Monte Carlo pricer* for path-dependent strategy indices.
- Risk
  - *Bump-and-revalue Delta* framework.

## Structure

```text
qis-pricing-engine/
├── CMakeLists.txt
├── README.md
├── include/
│   └── qis/
│       ├── core/        # utilities (types, RNG, time grid)
│       ├── market/      # curves and volatility
│       ├── model/       # stochastic models
│       ├── strategy/    # QIS strategy rules
│       ├── engine/      # index simulation
│       ├── product/     # payoffs
│       ├── pricing/     # pricers
│       └── risk/        # risk measures
├── src/
│   ├── engine/
│   ├── pricing/
│   └── risk/
└── apps/
    └── price_vol_target_call.cpp
