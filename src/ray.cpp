#include "ray.hpp"
#include "color.hpp"

Color Ray::color() const {
  auto unit = direction.unit();
  auto a = 0.5 * (unit.y + 1.0);
  Color c1 = {.r = 1, .g = 1, .b = 1};
  Color c2 = {.r = 0.5, .g = 0.7, .b = 1};
  return c1.lerp(c2, a);
}
