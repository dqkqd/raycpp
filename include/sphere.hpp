#pragma once

#include "hit.hpp"
#include "interval.hpp"
#include "point.hpp"
#include "vec3.hpp"
#include <optional>

class Sphere : public Hittable {
public:
  Sphere(Point center, double radius);

  [[nodiscard]] Vec3 outward_normal(const Point &at) const;

  [[nodiscard]] std::optional<HitRecord> hit(const Ray &ray,
                                             Interval interval) const override;

private:
  Point center_;
  double radius_;
};
