#pragma once

#include "hit.hpp"
#include "point.hpp"
#include "vec3.hpp"

class Sphere : public Hittable {
public:
  Sphere(Point center, double radius);

  [[nodiscard]] Vec3 outward_normal(const Point &at) const;

  [[nodiscard]] std::optional<HitRecord> hit(const Ray &ray) const override;

private:
  Point center_;
  double radius_;
};
