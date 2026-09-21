#include "sphere.hpp"
#include "point.hpp"
#include "vec3.hpp"

Vec3 Sphere::normal(const Point &at) const { return at - center; }
