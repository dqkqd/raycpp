#include "ray.hpp"

Point Ray::at(double t) const { return origin + t * direction; }
