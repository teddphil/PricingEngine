#pragma once
#include <cmath>
#include "model.hpp"
#include "qis/market/flat_curve.hpp"
#include "qis/market/flat_vol.hpp"

namespace qis {

class GbmModel final : public Model {
public:
  GbmModel(FlatCurve r, FlatCurve q, FlatVol vol)
    : r_(r), q_(q), vol_(vol) {}

  ModelState evolve(Real t, Real t_next, const ModelState& x, Real z) const override {
    Real dt = t_next - t;
    Real s  = x.spot;
    Real r  = r_.rate(t);
    Real q  = q_.rate(t);
    Real sig = vol_.sigma(t, s);

    // lognormal exact step
    Real mu = (r - q - 0.5 * sig * sig) * dt;
    Real sd = sig * std::sqrt(dt);
    Real s_next = s * std::exp(mu + sd * z);

    return ModelState{ s_next };
  }

private:
  FlatCurve r_;
  FlatCurve q_;
  FlatVol vol_;
};

} // namespace qis
