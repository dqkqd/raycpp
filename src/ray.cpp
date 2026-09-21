#include "ray.hpp"
#include "point.hpp"

Point Ray::at(double t) const { return origin + t * direction; }
