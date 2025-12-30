cmake_minimum_required(VERSION 3.20)
project(qis_pricing_engine VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(qis_engine
  src/core/timegrid.cpp
  src/core/rng.cpp
  src/market/flat_curve.cpp
  src/market/flat_vol.cpp
  src/model/gbm_model.cpp
  src/strategy/vol_target_strategy.cpp
  src/engine/index_simulator.cpp
  src/product/european_call.cpp
  src/pricing/mc_pricer.cpp
  src/risk/bump_risk.cpp
)

target_include_directories(qis_engine PUBLIC include)

add_executable(price_vol_target_call apps/price_vol_target_call.cpp)
target_link_libraries(price_vol_target_call PRIVATE qis_engine)

enable_testing()
# Hook for GoogleTest or Catch2 (intentionally left pluggable).
