#pragma once

#include "interval.hpp"
#include "ray.hpp"
#include <optional>

class AABB {
public:
  Interval x, y, z;

  AABB(const Interval &x, const Interval &y, const Interval &z);
  AABB(const Point &a, const Point &b);

  [[nodiscard]] std::optional<Interval> hit(const Ray &ray,
                                            const Interval &ray_t) const;

  [[nodiscard]] AABB merge(const AABB &other) const;

  static AABB empty();
};
