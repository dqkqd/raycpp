#pragma once

#include "point.hpp"
#include "vec3.hpp"

class Hittable;

class Ray {
public:
  Point origin_;
  Vec3 direction_;
  double time_;

  Ray(Point origin, Vec3 direction);
  Ray(Point origin, Vec3 direction, double time);

  [[nodiscard]] Point at(double t) const;
};
