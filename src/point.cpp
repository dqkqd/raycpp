#include "point.hpp"
#include "vec3.hpp"

Vec3 operator-(const Point &lhs, const Point &rhs) {
  return {.x = lhs.x - rhs.x, .y = lhs.y - rhs.y, .z = lhs.z - rhs.z};
}

Point operator+(const Point &p, const Vec3 &v) {
  return {.x = p.x + v.x, .y = p.y + v.y, .z = p.z + v.z};
}

Point operator-(const Point &p, const Vec3 &v) {
  return {.x = p.x - v.x, .y = p.y - v.y, .z = p.z - v.z};
}
