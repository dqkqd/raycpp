#include "ray.hpp"
#include "color.hpp"

Color Ray::color() const {
  Sphere s = {.center = {.x = 0, .y = 0, .z = -1}, .radius = 0.5};
  if (hit(s)) {
    return {.r = 1, .g = 0, .b = 0};
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

bool Ray::hit(const Sphere &sphere) const {
  auto oc = sphere.center - origin;
  auto a = direction.dot(direction);
  auto b = -2 * direction.dot(oc);
  auto c = oc.dot(oc) - (sphere.radius * sphere.radius);
  return (b * b) - (4 * a * c) >= 0;
}
