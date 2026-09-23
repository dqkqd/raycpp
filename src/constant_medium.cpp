#include "constant_medium.hpp"
#include "interval.hpp"
#include "material.hpp"
#include "texture.hpp"
#include "utils.hpp"
#include <algorithm>
#include <limits>

ConstantMedium::ConstantMedium(std::unique_ptr<Hittable> boundary,
                               double density, std::shared_ptr<Texture> tex)
    : boundary_(std::move(boundary)),
      phase_function_(std::make_shared<Isotropic>(std::move(tex))),
      neg_inv_density(-1.0 / density) {}

ConstantMedium::ConstantMedium(std::unique_ptr<Hittable> boundary,
                               double density, Color albedo)
    : boundary_(std::move(boundary)),
      phase_function_(std::make_shared<Isotropic>(albedo)),
      neg_inv_density(-1.0 / density) {}

AABB ConstantMedium::bounding_box() const { return boundary_->bounding_box(); }

std::optional<HitRecord> ConstantMedium::hit(const Ray &ray,
                                             Interval interval) const {
  // rec1 is the closest hit record
  auto rec1 = boundary_->hit(ray, Interval::universe());
  if (!rec1.has_value()) {
    return {};
  }

  // rec1 is the second closest hit record
  auto rec2 =
      boundary_->hit(ray, Interval{rec1->distance_ + 0.0001,
                                   std::numeric_limits<double>::infinity()});
  if (!rec2.has_value()) {
    return {};
  }

  rec1->distance_ = std::fmax(rec1->distance_, interval.min);
  rec2->distance_ = std::fmin(rec2->distance_, interval.max);

  if (rec1->distance_ >= rec2->distance_) {
    return {};
  }

  rec1->distance_ = std::max<double>(rec1->distance_, 0);
  auto ray_length = ray.direction_.length();

  // this is ray.at(rec1) - ray.at(rec2)
  auto distance_inside_boundary =
      (rec2->distance_ - rec1->distance_) * ray_length;

  auto hit_distance = neg_inv_density * std::log(random_double());
  if (hit_distance > distance_inside_boundary) {
    return {};
  }

  auto distance = rec1->distance_ + (hit_distance / ray_length);
  auto hit_point = ray.at(distance);
  Vec3 normal = {.x = 1, .y = 0, .z = 0};
  TextureCoordinate coord = {.u = 0, .v = 0};

  return HitRecord(hit_point, ray.direction_, normal, distance, phase_function_,
                   coord);
}
