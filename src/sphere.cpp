#include "sphere.hpp"
#include "aabb.hpp"
#include "hit.hpp"
#include "interval.hpp"
#include "material.hpp"
#include "point.hpp"
#include "ray.hpp"
#include "texture.hpp"
#include "vec3.hpp"
#include <cmath>
#include <memory>
#include <numbers>
#include <optional>
#include <utility>

Sphere::Sphere(Point center1, Point center2, double radius,
               std::shared_ptr<Material> material)
    : center_{center1, center2 - center1}, radius_(radius),
      material_(std::move(material)), bbox(AABB::empty()) {
  auto rvec = Vec3{.x = radius, .y = radius, .z = radius};
  auto bbox1 = AABB(center_.at(0) - rvec, center_.at(0) + rvec);
  auto bbox2 = AABB(center_.at(1) - rvec, center_.at(1) + rvec);
  bbox = bbox1.merge(bbox2);
};

Sphere::Sphere(Point center, double radius, std::shared_ptr<Material> material)
    : center_{center, Vec3{.x = 0, .y = 0, .z = 0}}, radius_(radius),
      material_(std::move(material)),
      bbox(center - Vec3{.x = radius, .y = radius, .z = radius},
           center + Vec3{.x = radius, .y = radius, .z = radius}) {}

TextureCoordinate Sphere::texture_coordinate(const Vec3 &p) {
  auto theta = std::acos(-p.y);
  auto phi = std::atan2(-p.z, p.x) + std::numbers::pi;

  return TextureCoordinate{.u = phi / (2 * std::numbers::pi),
                           .v = theta / std::numbers::pi};
}

std::optional<HitRecord> Sphere::hit(const Ray &ray, Interval interval) const {
  auto current_center = center_.at(ray.time_);
  auto oc = current_center - ray.origin_;
  auto a = ray.direction_.dot(ray.direction_);
  auto b = ray.direction_.dot(oc);
  auto c = oc.dot(oc) - (radius_ * radius_);
  auto delta = (b * b) - (a * c);
  if (delta < 0) {
    return {};
  }

  auto delta_s = sqrt(delta);

  auto distance = (b - delta_s) / a;
  if (!interval.surrounds(distance)) {
    distance = (b + delta_s) / a;
    if (!interval.surrounds(distance)) {
      return {};
    }
  }

  auto hit_point = ray.at(distance);
  auto normal = (hit_point - current_center) / radius_;

  auto coord = texture_coordinate(normal);

  return HitRecord(hit_point, ray.direction_, normal, distance, material_,
                   coord);
}

AABB Sphere::bounding_box() const { return bbox; }
