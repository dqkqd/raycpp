#pragma once

class Interval {
public:
  double tmin, tmax;

  [[nodiscard]] bool surround(double x) const;
  [[nodiscard]] double clamp(double x) const;
  [[nodiscard]] Interval expand(double delta) const;

  [[nodiscard]] Interval merge(const Interval &other) const;

  static Interval empty();
};
