#pragma once

#include "hit.hpp"
#include "interval.hpp"
#include <memory>
#include <vector>

class World : public Hittable {
public:
  void add(std::unique_ptr<Hittable> &&object);

  [[nodiscard]] std::optional<HitRecord> hit(const Ray &ray,
                                             Interval interval) const override;

private:
  std::vector<std::unique_ptr<Hittable>> objects;
};
