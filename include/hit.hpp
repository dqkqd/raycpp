#pragma once

#include "point.hpp"
#include "vec3.hpp"

class HitRecord {
public:
  Point hit_point;
  Vec3 normal;

  double distance;
};
