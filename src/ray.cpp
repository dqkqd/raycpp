#include "ray.hpp"
#include "color.hpp"
#include "hit.hpp"
#include <cmath>
#include <optional>

Color Ray::color() const {
  Sphere s = {.center = {.x = 0, .y = 0, .z = -1}, .radius = 0.5};

  auto rec = hit(s);
  if (rec.has_value()) {
    auto unit_normal = rec->normal;
    Color c = {.r = unit_normal.x, .g = unit_normal.y, .b = unit_normal.z};
    return c.lerp({.r = 1, .g = 1, .b = 1}, 0.5);
  }
  return background_color();
}

Color Ray::background_color() const {
  auto unit = direction.unit();
  auto a = 0.5 * (unit.y + 1.0);
  Color c1 = {.r = 1, .g = 1, .b = 1};
  Color c2 = {.r = 0.5, .g = 0.7, .b = 1};
  return c1.lerp(c2, a);
}

Point Ray::at(double t) const { return origin + t * direction; }

std::optional<HitRecord> Ray::hit(const Sphere &sphere) const {
  auto oc = sphere.center - origin;
  auto a = direction.dot(direction);
  auto b = direction.dot(oc);
  auto c = oc.dot(oc) - (sphere.radius * sphere.radius);
  auto delta = (b * b) - (a * c);
  if (delta < 0) {
    return {};
  }

  auto delta_s = sqrt(delta);

  auto distance = (b - delta_s) / a;
  auto hit_point = at(distance);
  auto normal = sphere.normal(hit_point).unit();

  return HitRecord{
      .hit_point = hit_point, .normal = normal, .distance = distance};
}
