#pragma once

class Interval {
public:
  double min, max;

  Interval(double tmin, double tmax) noexcept;

  [[nodiscard]] bool surrounds(double x) const;
  [[nodiscard]] bool contains(double x) const;
  [[nodiscard]] double clamp(double x) const;
  [[nodiscard]] Interval expand(double delta) const;
  [[nodiscard]] double size() const;
  [[nodiscard]] Interval merge(const Interval &other) const;

  static Interval empty();
};
