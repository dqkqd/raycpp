#include "material.hpp"
#include "hit.hpp"
#include "vec3.hpp"
#include <algorithm>
#include <optional>

Lambertian::Lambertian(Color albedo) : albedo_(albedo) {};

std::optional<Scatter> Lambertian::scatter(const Ray & /*ray*/,
                                           const HitRecord &rec) const {
  auto direction = rec.normal_ + Vec3::random_unit();
  if (direction.near_zero()) {
    direction = rec.normal_;
  }
  return Scatter{.scattered =
                     Ray{.origin = rec.hit_point_, .direction = direction},
                 .attenuation = albedo_};
}

Metal::Metal(Color albedo, double fuzz)
    : albedo_(albedo), fuzz_(std::min(fuzz, 1.0)) {};

std::optional<Scatter> Metal::scatter(const Ray &ray,
                                      const HitRecord &rec) const {
  auto direction = ray.direction.reflect(rec.normal_);
  direction = direction.unit() + fuzz_ * Vec3::random_unit();
  if (direction.dot(rec.normal_) <= 0) {
    return {};
  }
  return Scatter{.scattered =
                     Ray{.origin = rec.hit_point_, .direction = direction},
                 .attenuation = albedo_};
}
