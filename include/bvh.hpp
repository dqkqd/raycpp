#pragma once

#include "hit.hpp"
#include "interval.hpp"
#include "world.hpp"
#include <memory>
#include <vector>

// A binary tree
class BvhNode : public Hittable {
public:
  explicit BvhNode(World &&world);
  explicit BvhNode(std::vector<std::unique_ptr<Hittable>> objects);

  [[nodiscard]] std::optional<HitRecord> hit(const Ray &ray,
                                             Interval interval) const override;

  [[nodiscard]] AABB bounding_box() const override;

private:
  std::unique_ptr<Hittable> left;
  std::unique_ptr<Hittable> right;

  AABB bbox = AABB::empty();
};
