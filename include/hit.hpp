#pragma once

#include "aabb.hpp"
#include "interval.hpp"
#include "material.hpp"
#include "point.hpp"
#include "ray.hpp"
#include "vec3.hpp"
#include <cstdint>
#include <memory>
#include <optional>

class HitRecord {

public:
  enum class Direction : std::uint8_t { Inward, Outward };

  Point hit_point_;
  Direction direction_;
  Vec3 normal_;
  double distance_;
  std::shared_ptr<Material> material_;

  HitRecord(Point hit_point, Direction direction, Vec3 normal, double distance,
            std::shared_ptr<Material> material);
};

class Hittable {
public:
  Hittable() = default;
  Hittable(const Hittable &) = delete;
  Hittable(Hittable &&) = delete;
  Hittable &operator=(const Hittable &) = delete;
  Hittable &operator=(Hittable &&) = delete;

  virtual ~Hittable() = default;
  [[nodiscard]] virtual std::optional<HitRecord>
  hit(const Ray &ray, Interval interval) const = 0;

  [[nodiscard]] virtual AABB bounding_box() const = 0;

  static bool box_x_compare(const std::unique_ptr<Hittable> &lhs,
                            const std::unique_ptr<Hittable> &rhs);
  static bool box_y_compare(const std::unique_ptr<Hittable> &lhs,
                            const std::unique_ptr<Hittable> &rhs);
  static bool box_z_compare(const std::unique_ptr<Hittable> &lhs,
                            const std::unique_ptr<Hittable> &rhs);
};
