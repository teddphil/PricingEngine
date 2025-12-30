# QIS Pricing Engine

- MarketData: spot, curves, dividend yields, vol surfaces, correlations
- Models: risk-neutral dynamics (single-asset GBM to start)
- Strategies: rules that map state → weights/positions and rebalance schedule
- Index/Portfolio Engine: applies strategy, generates index path (incl. costs/fees)
- Products: payoff on index path (option, swap, note)
- Pricers: Monte Carlo (primary for dynamic/path-dependent QIS)
- Risk: bump-and-revalue + scenarios (extendable to AAD later)
- Infra: date/time grid, RNG, config, logging, error handling
- Tests/Docs: unit tests and model validation notes
