#pragma once

#include "aabb.hpp"
#include "hit.hpp"
#include "vec3.hpp"

class Translate : public Hittable {
public:
  Translate(std::unique_ptr<Hittable> object, Vec3 offset);

  [[nodiscard]] std::optional<HitRecord> hit(const Ray &ray,
                                             Interval interval) const override;

  [[nodiscard]] AABB bounding_box() const override;

private:
  std::unique_ptr<Hittable> object_;
  Vec3 offset_;
  AABB bbox = AABB::empty();
};

class RotateY : public Hittable {
public:
  RotateY(std::unique_ptr<Hittable> object, double angle);

  [[nodiscard]] std::optional<HitRecord> hit(const Ray &ray,
                                             Interval interval) const override;

  [[nodiscard]] AABB bounding_box() const override;

private:
  std::unique_ptr<Hittable> object_;
  double sin_theta;
  double cos_theta;
  AABB bbox = AABB::empty();
};
