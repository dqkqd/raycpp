#include "transform.hpp"
#include "utils.hpp"
#include "vec3.hpp"
#include <cmath>
#include <limits>

Translate::Translate(std::unique_ptr<Hittable> object, Vec3 offset)
    : object_(std::move(object)), offset_(offset) {
  bbox = bbox.merge(object_->bounding_box() + offset);
}

std::optional<HitRecord> Translate::hit(const Ray &ray,
                                        Interval interval) const {
  Ray offset_r{ray.origin_ - offset_, ray.direction_, ray.time_};
  auto rec = object_->hit(offset_r, interval);
  if (!rec) {
    return {};
  }
  rec->hit_point_ = rec->hit_point_ + offset_;
  return rec;
}

AABB Translate::bounding_box() const { return bbox; }

RotateY::RotateY(std::unique_ptr<Hittable> object, double angle)
    : object_(std::move(object)) {
  auto radians = degree_to_radian(angle);
  sin_theta = std::sin(radians);
  cos_theta = std::cos(radians);

  bbox = object_->bounding_box();

  Point min{
      .x = std::numeric_limits<double>::infinity(),
      .y = std::numeric_limits<double>::infinity(),
      .z = std::numeric_limits<double>::infinity(),
  };

  Point max{
      .x = -std::numeric_limits<double>::infinity(),
      .y = -std::numeric_limits<double>::infinity(),
      .z = -std::numeric_limits<double>::infinity(),
  };

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      for (int k = 0; k < 2; k++) {

        auto x = (i * bbox.x.max) + ((1 - i) * bbox.x.min);
        auto y = (j * bbox.y.max) + ((1 - j) * bbox.y.min);
        auto z = (k * bbox.z.max) + ((1 - k) * bbox.z.min);

        auto newx = (cos_theta * x) + (sin_theta * z);
        auto newz = (-sin_theta * x) + (cos_theta * z);

        min.x = std::fmin(min.x, newx);
        min.y = std::fmin(min.y, y);
        min.z = std::fmin(min.z, newz);

        max.x = std::fmax(max.x, newx);
        max.y = std::fmax(max.y, y);
        max.z = std::fmax(max.z, newz);
      }
    }
  }

  bbox = AABB(min, max);
}

std::optional<HitRecord> RotateY::hit(const Ray &ray, Interval interval) const {

  Point origin = {
      .x = (cos_theta * ray.origin_.x) - (sin_theta * ray.origin_.z),
      .y = ray.origin_.y,
      .z = (sin_theta * ray.origin_.x) + (cos_theta * ray.origin_.z)};

  Vec3 direction = {
      .x = (cos_theta * ray.direction_.x) - (sin_theta * ray.direction_.z),
      .y = ray.direction_.y,
      .z = (sin_theta * ray.direction_.x) + (cos_theta * ray.direction_.z)};

  Ray rotated_r{origin, direction, ray.time_};
  auto rec = object_->hit(rotated_r, interval);
  if (!rec) {
    return {};
  }

  rec->hit_point_ = {
      .x = (cos_theta * rec->hit_point_.x) + (sin_theta * rec->hit_point_.z),
      .y = rec->hit_point_.y,
      .z = (-sin_theta * rec->hit_point_.x) + (cos_theta * rec->hit_point_.z)};

  rec->normal_ = {
      .x = (cos_theta * rec->normal_.x) + (sin_theta * rec->normal_.z),
      .y = rec->normal_.y,
      .z = (-sin_theta * rec->normal_.x) + (cos_theta * rec->normal_.z)};

  return rec;
}

AABB RotateY::bounding_box() const { return bbox; }
