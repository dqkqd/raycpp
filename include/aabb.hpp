#pragma once

#include "interval.hpp"
#include "point.hpp"
#include "ray.hpp"
#include <cstdint>
#include <optional>

class AABB {
public:
  enum class Axis : std::uint8_t { X, Y, Z };

  Interval x, y, z;

  AABB(const Interval &xi, const Interval &yi, const Interval &zi) noexcept;
  AABB(const Point &a, const Point &b);

  [[nodiscard]] std::optional<Interval> hit(const Ray &ray,
                                            const Interval &ray_t) const;

  [[nodiscard]] AABB merge(const AABB &other) const;

  [[nodiscard]] Axis longest_axis() const;

  static AABB empty();

  friend AABB operator+(const AABB &bbox, const Vec3 &offset);

private:
  void pad_to_minimums();
};
