#pragma once

#include "point.hpp"
#include "vec3.hpp"

class Sphere {
public:
  Point center;
  double radius;

  [[nodiscard]] Vec3 normal(const Point &at) const;
};
