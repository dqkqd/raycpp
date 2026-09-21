#include "ray.hpp"
#include "color.hpp"
#include "hit.hpp"

Color Ray::color(const Hittable &hittable) const {
  auto rec = hittable.hit(*this);
  if (rec.has_value()) {
    auto unit_normal = rec->normal_;
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
