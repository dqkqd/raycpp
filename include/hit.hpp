#pragma once

#include "point.hpp"
#include "ray.hpp"
#include "vec3.hpp"

class HitRecord {
public:
  Point hit_point;
  Vec3 normal;

  double distance;
};

class Hittable {
public:
  Hittable() = default;
  Hittable(const Hittable &) = delete;
  Hittable(Hittable &&) = delete;
  Hittable &operator=(const Hittable &) = delete;
  Hittable &operator=(Hittable &&) = delete;

  virtual ~Hittable() = default;
  [[nodiscard]] virtual std::optional<HitRecord> hit(const Ray &ray) const = 0;
};
