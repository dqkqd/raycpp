#pragma once

#include "vec3.hpp"

class Point {
public:
  double x, y, z;

  // point - point is vector
  friend Vec3 operator-(const Point &lhs, const Point &rhs);

  friend Point operator+(const Point &p, const Vec3 &v);
  friend Point operator-(const Point &p, const Vec3 &v);
  friend Point operator*(const Point &p, double s);
};
