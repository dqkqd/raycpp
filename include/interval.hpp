#pragma once

class Interval {
public:
  double tmin, tmax;

  [[nodiscard]] bool surround(double x) const;
};
