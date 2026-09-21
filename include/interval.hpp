#pragma once

class Interval {
public:
  double tmin, tmax;

  [[nodiscard]] bool surround(double x) const;
  [[nodiscard]] double clamp(double x) const;
};
