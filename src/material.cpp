#include "material.hpp"
#include "color.hpp"
#include "hit.hpp"
#include "point.hpp"
#include "ray.hpp"
#include "texture.hpp"
#include "utils.hpp"
#include "vec3.hpp"
#include <algorithm>
#include <cmath>
#include <memory>
#include <optional>
#include <utility>

Lambertian::Lambertian(const Color &color)
    : tex_(std::make_shared<SolidColor>(color)) {};
Lambertian::Lambertian(std::shared_ptr<Texture> tex) : tex_(std::move(tex)) {};

std::optional<Scatter> Lambertian::scatter(const Ray &ray,
                                           const HitRecord &rec) const {
  auto direction = rec.normal_ + Vec3::random_unit();
  if (direction.near_zero()) {
    direction = rec.normal_;
  }
  auto scattered = Ray{rec.hit_point_, direction, ray.time_};
  return Scatter{.scattered = scattered,
                 .attenuation = tex_->value(rec.coord_, rec.hit_point_)};
}

Metal::Metal(Color albedo, double fuzz)
    : albedo_(albedo), fuzz_(std::min(fuzz, 1.0)) {};

std::optional<Scatter> Metal::scatter(const Ray &ray,
                                      const HitRecord &rec) const {
  auto reflected = ray.direction_.reflect(rec.normal_);
  reflected = reflected.unit() + fuzz_ * Vec3::random_unit();
  auto scattered = Ray{rec.hit_point_, reflected, ray.time_};
  if (scattered.direction_.dot(rec.normal_) <= 0) {
    return {};
  }
  return Scatter{.scattered = scattered, .attenuation = albedo_};
}

Dielectrics::Dielectrics(double refraction_index)
    : refraction_index_(refraction_index) {};

std::optional<Scatter> Dielectrics::scatter(const Ray &ray,
                                            const HitRecord &rec) const {

  static const auto attenuation = Color{.r = 1, .g = 1, .b = 1};

  auto unit_direction = ray.direction_.unit();
  auto cos_theta = std::fmin(-unit_direction.dot(rec.normal_), 1.0);
  auto sin_theta = sqrt(1 - (cos_theta * cos_theta));

  double ri = 0.0;
  switch (rec.direction_) {
  case HitRecord::Direction::Inward:
    // ray is inside the object
    ri = refraction_index_;
    break;
  case HitRecord::Direction::Outward:
    ri = 1.0 / refraction_index_;
    break;
  }

  auto cannot_refract = ri * sin_theta > 1.0;
  if (cannot_refract || refelectance(cos_theta, ri) > random_double()) {
    auto reflected = unit_direction.reflect(rec.normal_);
    auto scattered = Ray{rec.hit_point_, reflected, ray.time_};
    return Scatter{.scattered = scattered, .attenuation = attenuation};
  }

  auto refracted = unit_direction.refract(rec.normal_, ri);
  auto scattered = Ray{rec.hit_point_, refracted, ray.time_};
  return Scatter{.scattered = scattered, .attenuation = attenuation};
}

DiffuseLight::DiffuseLight(std::shared_ptr<Texture> tex)
    : tex_(std::move(tex)) {}
DiffuseLight::DiffuseLight(const Color &emit)
    : tex_(std::make_shared<SolidColor>(emit)) {}

Color DiffuseLight::emitted(const TextureCoordinate &coord,
                            const Point &p) const {
  return tex_->value(coord, p);
}
