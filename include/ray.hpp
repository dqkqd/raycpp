#pragma once

#include "color.hpp"
#include "point.hpp"
#include "vec3.hpp"

class Hittable;

class Ray {
public:
  Point origin;
  Vec3 direction;

  [[nodiscard]] Color color(const Hittable &hittable) const;

  [[nodiscard]] Point at(double t) const;

private:
  [[nodiscard]] Color background_color() const;
};
