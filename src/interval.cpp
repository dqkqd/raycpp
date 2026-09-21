#include "interval.hpp"

bool Interval::surround(double x) const { return tmin < x && x < tmax; }
