#pragma once

#include <limits>

class Interval {
public:
  double min, max;

  constexpr Interval(double tmin, double tmax) noexcept
      : min(tmin), max(tmax) {}

  [[nodiscard]] bool surround(double x) const;
  [[nodiscard]] double clamp(double x) const;
  [[nodiscard]] Interval expand(double delta) const;
  [[nodiscard]] double size() const;

  [[nodiscard]] Interval merge(const Interval &other) const;

  static const Interval empty;
};

inline constexpr Interval Interval::empty{
    std::numeric_limits<double>::infinity(),
    -std::numeric_limits<double>::infinity()};
