#pragma once

#include "point.hpp"
#include "ray.hpp"
#include "vec3.hpp"

class HitRecord {

public:
  enum class Direction : uint8_t { Inward, Outward };

  Point hit_point_;
  Direction direction_;
  Vec3 normal_;
  double distance_;

  HitRecord(Point hit_point, Direction direction, Vec3 normal, double distance);
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
