#pragma once

class Vec3 {
public:
  double x, y, z;

  // scalar operator
  friend Vec3 operator*(const Vec3 &v, double s);
  friend Vec3 operator*(double s, const Vec3 &v);
  friend Vec3 operator/(const Vec3 &v, double s);

  // vector operator
  friend Vec3 operator+(const Vec3 &lhs, const Vec3 &rhs);

  friend bool operator==(const Vec3 &lhs, const Vec3 &rhs);

  [[nodiscard]] double length_square() const;
  [[nodiscard]] double length() const;
  [[nodiscard]] Vec3 unit() const;
};
