#include "interval.hpp"
#include <algorithm>
#include <limits>

Interval::Interval(double tmin, double tmax) noexcept : min(tmin), max(tmax) {}

bool Interval::surround(double x) const { return min < x && x < max; }

double Interval::clamp(double x) const {
  if (x < min) {
    return min;
  }
  if (x > max) {
    return max;
  }
  return x;
}

Interval Interval::expand(double delta) const {
  auto padding = delta / 2;
  return {min - padding, max + padding};
}

Interval Interval::merge(const Interval &other) const {
  return {std::min(min, other.min), std::max(max, other.max)};
}

double Interval::size() const { return max - min; }

Interval Interval::empty() {
  return {std::numeric_limits<double>::infinity(),
          -std::numeric_limits<double>::infinity()};
}
