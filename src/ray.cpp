#include "ray.hpp"
#include "point.hpp"

Ray::Ray(Point origin, Vec3 direction, double time)
    : origin_(origin), direction_(direction), time_(time) {}

Ray::Ray(Point origin, Vec3 direction) : Ray(origin, direction, 0) {}

Point Ray::at(double t) const { return origin_ + t * direction_; }
