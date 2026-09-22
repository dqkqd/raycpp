#include "world.hpp"
#include "aabb.hpp"
#include "hit.hpp"
#include "interval.hpp"
#include "ray.hpp"
#include <memory>
#include <optional>
#include <utility>

World::World(World &&w) noexcept
    : objects(std::move(w.objects)), bbox(w.bbox) {}

World &World::operator=(World &&w) noexcept {
  if (this != &w) {
    objects = std::move(w.objects);
    bbox = w.bbox;
  }
  return *this;
}

void World::add(std::unique_ptr<Hittable> &&object) {
  bbox = bbox.merge(object->bounding_box());
  objects.push_back(std::move(object));
}

std::optional<HitRecord> World::hit(const Ray &ray, Interval interval) const {
  std::optional<HitRecord> best = {};

  for (const auto &object : objects) {
    // TODO(khanhdq): return the distance, construct the hit record later
    auto rec = object->hit(ray, interval);
    if (rec.has_value()) {
      best = rec;
      interval.max = best->distance_;
    }
  }
  return best;
}

AABB World::bounding_box() const { return bbox; }
