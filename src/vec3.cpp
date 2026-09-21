#include "vec3.hpp"
#include <cmath>

Vec3 operator*(const Vec3 &v, double s) {
  return {.x = v.x * s, .y = v.y * s, .z = v.z * s};
}

Vec3 operator*(double s, const Vec3 &v) { return v * s; }

Vec3 operator/(const Vec3 &v, double s) {
  return {.x = v.x / s, .y = v.y / s, .z = v.z / s};
}

Vec3 operator+(const Vec3 &lhs, const Vec3 &rhs) {
  return {.x = lhs.x + rhs.x, .y = lhs.y + rhs.y, .z = lhs.z + rhs.z};
}

double Vec3::length_square() const { return (x * x) + (y * y) + (z * z); }

double Vec3::length() const { return sqrt(length_square()); }

Vec3 Vec3::unit() const { return *this / length(); }

bool operator==(const Vec3 &lhs, const Vec3 &rhs) {
  return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}
