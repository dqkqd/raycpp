#pragma once

#include "hit.hpp"
#include "interval.hpp"
#include "material.hpp"
#include "point.hpp"
#include <memory>
#include <optional>

class Sphere : public Hittable {
public:
  Sphere(Point center, double radius, std::shared_ptr<Material> material);
  Sphere(Point center1, Point center2, double radius,
         std::shared_ptr<Material> material);

  [[nodiscard]] std::optional<HitRecord> hit(const Ray &ray,
                                             Interval interval) const override;

private:
  Ray center_;
  double radius_;
  std::shared_ptr<Material> material_;
};
