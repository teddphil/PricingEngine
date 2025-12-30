# QIS Pricing Engine (C++)

A C++20 **pricing and risk-management framework** for **Quantitative Investment Strategies (QIS)** and derivatives written on **dynamic investment strategy indices**.

This project demonstrates how a front-office quantitative analytics library can:
- simulate **rules-based investment strategies** (e.g. volatility targeting),
- price **derivatives on strategy indices** via Monte Carlo,
- and produce **risk sensitivities** in a clean, extensible design.

The code is intentionally structured to resemble a **real FO Quant / QA codebase** used for equities and equity-hybrid products.

---

## Key Features

### Strategy & Index Modelling
- Dynamic **volatility-targeting strategy**
- Discrete rebalancing with cash allocation
- Index construction driven by asset returns
- Extensible strategy interface (trend, CPPI, risk parity, etc.)

### Market & Models
- Risk-neutral **Geometric Brownian Motion (GBM)**
- Flat interest rate, dividend yield, and volatility (for clarity)
- Clean separation between **market data**, **model**, and **strategy**

### Pricing
- **Monte Carlo pricer** for path-dependent strategy indices
- Deterministic seeding for reproducibility
- Standard error reporting

### Risk
- **Bump-and-revalue Delta** framework
- Designed to be extended to Vega, scenarios, and stress testing

### Engineering Quality
- Modern **C++20**
- Header-only components where appropriate
- Out-of-source CMake build
- Clear separation of concerns
- Interview-ready design and documentation

---

## Project Structure

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
