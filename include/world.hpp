#pragma once

#include "aabb.hpp"
#include "hit.hpp"
#include "interval.hpp"
#include <memory>
#include <vector>

class World : public Hittable {
public:
  friend class BvhNode;

  World() = default;

  World(World &&w) noexcept;
  World &operator=(World &&w) noexcept;

  // no copy
  World(const World &) = delete;
  World &operator=(const World &) = delete;

  ~World() override = default;

  void add(std::unique_ptr<Hittable> &&object);
  [[nodiscard]] std::optional<HitRecord> hit(const Ray &ray,
                                             Interval interval) const override;

  [[nodiscard]] AABB bounding_box() const override;

private:
  std::vector<std::unique_ptr<Hittable>> objects;

  AABB bbox = AABB::empty();
};
