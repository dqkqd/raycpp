#pragma once

#include "color.hpp"
#include "point.hpp"
#include "vec3.hpp"

class Ray {
public:
  Point origin;
  Vec3 direction;

  [[nodiscard]] Color color() const;
};
