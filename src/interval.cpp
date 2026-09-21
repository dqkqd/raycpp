#include "interval.hpp"

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
