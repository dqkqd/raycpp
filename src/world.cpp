#include "world.hpp"
#include "hit.hpp"
#include "interval.hpp"
#include "ray.hpp"
#include <memory>
#include <optional>
#include <utility>

void World::add(std::unique_ptr<Hittable> &&object) {
  objects.push_back(std::move(object));
}

std::optional<HitRecord> World::hit(const Ray &ray, Interval interval) const {
  std::optional<HitRecord> best = {};

  for (const auto &object : objects) {
    auto rec = object->hit(ray, interval);
    if (rec.has_value()) {
      best = rec;
      interval.tmax = best->distance_;
    }
  }
  return best;
}
