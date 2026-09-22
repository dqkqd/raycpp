#include "aabb.hpp"
#include "interval.hpp"
#include "point.hpp"
#include "ray.hpp"
#include <algorithm>
#include <optional>

AABB::AABB(const Interval &xi, const Interval &yi, const Interval &zi)
    : x(xi), y(yi), z(zi) {}
AABB::AABB(const Point &a, const Point &b)
    : x(a.x <= b.x ? Interval{a.x, b.x} : Interval{b.x, a.x}),
      y(a.y <= b.y ? Interval{a.y, b.y} : Interval{b.y, a.y}),
      z(a.z <= b.z ? Interval{a.z, b.z} : Interval{b.z, a.z}) {}

std::optional<Interval> AABB::hit(const Ray &ray, const Interval &ray_t) const {
  auto tmin = ray_t.min;
  auto tmax = ray_t.max;

  auto slab_assign = [&](const Interval &slab, double origin,
                         double direction) {
    auto t0 = (slab.min - origin) / direction;
    auto t1 = (slab.max - origin) / direction;
    auto p = std::minmax(t0, t1);
    tmin = std::max(tmin, p.first);
    tmax = std::min(tmax, p.second);
  };

  slab_assign(x, ray.origin_.x, ray.direction_.x);
  slab_assign(y, ray.origin_.y, ray.direction_.y);
  slab_assign(z, ray.origin_.z, ray.direction_.z);

  if (tmin >= tmax) {
    return {};
  }

  return Interval{tmin, tmax};
}

AABB AABB::merge(const AABB &other) const {
  return {x.merge(other.x), y.merge(other.y), z.merge(other.z)};
}

AABB AABB::empty() {
  return {Interval::empty(), Interval::empty(), Interval::empty()};
}
