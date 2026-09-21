#pragma once

#include "point.hpp"
#include "vec3.hpp"

class Hittable;

class Ray {
public:
  Point origin;
  Vec3 direction;

  [[nodiscard]] Point at(double t) const;
};
