#include "sphere.hpp"
#include "hit.hpp"
#include "point.hpp"
#include "vec3.hpp"
#include <cmath>

Sphere::Sphere(Point center, double radius)
    : center_(center), radius_(radius) {};

Vec3 Sphere::outward_normal(const Point &at) const { return at - center_; }

std::optional<HitRecord> Sphere::hit(const Ray &ray) const {
  auto oc = center_ - ray.origin;
  auto a = ray.direction.dot(ray.direction);
  auto b = ray.direction.dot(oc);
  auto c = oc.dot(oc) - (radius_ * radius_);
  auto delta = (b * b) - (a * c);
  if (delta < 0) {
    return {};
  }

  auto delta_s = sqrt(delta);

  auto distance = (b - delta_s) / a;
  auto hit_point = ray.at(distance);
  auto normal = outward_normal(hit_point).unit();

  return HitRecord{
      .hit_point = hit_point, .normal = normal, .distance = distance};
}
