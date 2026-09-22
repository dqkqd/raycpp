#include "vec3.hpp"
#include "utils.hpp"
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

Vec3 operator-(const Vec3 &lhs, const Vec3 &rhs) {
  return {.x = lhs.x - rhs.x, .y = lhs.y - rhs.y, .z = lhs.z - rhs.z};
}

Vec3 Vec3::operator-() const { return {.x = -x, .y = -y, .z = -z}; }

double Vec3::dot(const Vec3 &other) const {
  return (x * other.x) + (y * other.y) + (z * other.z);
}

Vec3 Vec3::cross(const Vec3 &other) const {
  return {
      .x = (y * other.z) - (z * other.y),
      .y = (z * other.x) - (x * other.z),
      .z = (x * other.y) - (y * other.x),
  };
}

bool Vec3::near_zero() const {
  static const auto s = 1e-8;
  return fabs(x) < s && fabs(y) < s && fabs(z) < s;
}

double Vec3::length_square() const { return (x * x) + (y * y) + (z * z); }

double Vec3::length() const { return sqrt(length_square()); }

Vec3 Vec3::unit() const { return *this / length(); }

bool operator==(const Vec3 &lhs, const Vec3 &rhs) {
  return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

Vec3 Vec3::random() {
  return {.x = random_double(), .y = random_double(), .z = random_double()};
}

Vec3 Vec3::random(double min, double max) {
  return {.x = random_double(min, max),
          .y = random_double(min, max),
          .z = random_double(min, max)};
}

Vec3 Vec3::random_unit() {
  while (true) {
    auto vec = random(-1, 1);
    auto lensq = vec.length_square();
    if (1e-160 < lensq && lensq <= 1) {
      return vec / sqrt(lensq);
    }
  }
}

Vec3 Vec3::random_in_unit_disk() {
  while (true) {
    Vec3 p = {.x = random_double(-1, 1), .y = random_double(-1, 1), .z = 0};
    if (p.length_square() <= 1) {
      return p;
    }
  }
}

Vec3 Vec3::reflect(const Vec3 &normal) const {
  return *this - 2 * dot(normal) * normal;
}

Vec3 Vec3::refract(const Vec3 &normal, double ri) const {
  auto cos_theta = std::fmin(-dot(normal), 1.0);
  auto r_perp = ri * (*this + cos_theta * normal);
  auto r_parallel = -sqrt(fabs(1 - r_perp.length_square())) * normal;
  return r_perp + r_parallel;
}
