#pragma once

#include "interval.hpp"
#include "ray.hpp"
#include <optional>

class AABB {
public:
  Interval x, y, z;

  constexpr AABB(const Interval &xi, const Interval &yi,
                 const Interval &zi) noexcept
      : x(xi), y(yi), z(zi) {}

  AABB(const Point &a, const Point &b);

  [[nodiscard]] std::optional<Interval> hit(const Ray &ray,
                                            const Interval &ray_t) const;

  [[nodiscard]] AABB merge(const AABB &other) const;

  static const AABB empty;
};

inline constexpr AABB AABB::empty{Interval::empty, Interval::empty,
                                  Interval::empty};
