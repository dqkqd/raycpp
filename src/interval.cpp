#include "interval.hpp"
#include <algorithm>
#include <limits>

bool Interval::surround(double x) const { return tmin < x && x < tmax; }

double Interval::clamp(double x) const {
  if (x < tmin) {
    return tmin;
  }
  if (x > tmax) {
    return tmax;
  }
  return x;
}

Interval Interval::expand(double delta) const {
  auto padding = delta / 2;
  return {.tmin = tmin - padding, .tmax = tmax + padding};
}

Interval Interval::merge(const Interval &other) const {
  return {
      .tmin = std::min(tmin, other.tmin),
      .tmax = std::max(tmax, other.tmax),
  };
}

Interval Interval::empty() {
  return {.tmin = std::numeric_limits<double>::infinity(),
          .tmax = -std::numeric_limits<double>::infinity()};
}
