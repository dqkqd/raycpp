#include "sphere.hpp"
#include "hit.hpp"
#include "interval.hpp"
#include "material.hpp"
#include "point.hpp"
#include "ray.hpp"
#include "vec3.hpp"
#include <cmath>
#include <memory>
#include <optional>
#include <utility>

Sphere::Sphere(Point center1, Point center2, double radius,
               std::shared_ptr<Material> material)
    : center_{center1, center2 - center1}, radius_(radius),
      material_(std::move(material)),
      bbox{center1 - Vec3{.x = radius, .y = radius, .z = radius},
           center2 + Vec3{.x = radius, .y = radius, .z = radius}} {};

Sphere::Sphere(Point center, double radius, std::shared_ptr<Material> material)
    : Sphere(center, center, radius, std::move(material)) {}

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
  if (!interval.surround(distance)) {
    distance = (b + delta_s) / a;
    if (!interval.surround(distance)) {
      return {};
    }
  }

  auto hit_point = ray.at(distance);
  auto normal = (hit_point - current_center) / radius_;

  if (normal.dot(ray.direction_) > 0) {
    return HitRecord(hit_point, HitRecord::Direction::Inward, -normal, distance,
                     material_);
  }
  return HitRecord(hit_point, HitRecord::Direction::Outward, normal, distance,
                   material_);
}

AABB Sphere::bounding_box() const { return bbox; }
