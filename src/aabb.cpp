#include "aabb.hpp"
#include "interval.hpp"
#include <algorithm>
#include <optional>

AABB::AABB(const Interval &x, const Interval &y, const Interval &z)
    : x(x), y(y), z(z) {}
AABB::AABB(const Point &a, const Point &b)
    : x(a.x <= b.x ? Interval{.tmin = a.x, .tmax = b.x}
                   : Interval{.tmin = b.x, .tmax = a.x}),
      y(a.y <= b.y ? Interval{.tmin = a.y, .tmax = b.y}
                   : Interval{.tmin = b.y, .tmax = a.y}),
      z(a.z <= b.z ? Interval{.tmin = a.z, .tmax = b.z}
                   : Interval{.tmin = b.z, .tmax = a.z}) {}

std::optional<Interval> AABB::hit(const Ray &ray, const Interval &ray_t) const {
  auto tmin = ray_t.tmin;
  auto tmax = ray_t.tmax;

  auto slab_assign = [&](const Interval &slab, double origin,
                         double direction) {
    auto t0 = (slab.tmin - origin) / direction;
    auto t1 = (slab.tmax - origin) / direction;
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

  return Interval{.tmin = tmin, .tmax = tmax};
}

AABB AABB::merge(const AABB &other) const {
  return {x.merge(other.x), y.merge(other.y), z.merge(other.z)};
}

AABB AABB::empty() {
  return {Interval::empty(), Interval::empty(), Interval::empty()};
}
