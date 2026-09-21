#pragma once

#include "color.hpp"
#include "point.hpp"
#include "sphere.hpp"
#include "vec3.hpp"

class Ray {
public:
  Point origin;
  Vec3 direction;

  [[nodiscard]] Color color() const;

  [[nodiscard]] bool hit(const Sphere &sphere) const;

private:
  [[nodiscard]] Color background_color() const;
};
