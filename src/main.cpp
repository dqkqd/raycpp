#include "camera.hpp"
#include "material.hpp"
#include "point.hpp"
#include "sphere.hpp"
#include "world.hpp"
#include <memory>

int main() {
  auto cam = Camera::init(16.0 / 9.0, 400, 100, 50, 90);

  auto world = World();

  auto R = std::cos(std::numbers::pi / 4);

  auto material_left =
      std::make_shared<Lambertian>(Color{.r = 0, .g = 0, .b = 1});
  auto material_right =
      std::make_shared<Lambertian>(Color{.r = 1, .g = 0, .b = 0});

  world.add(std::make_unique<Sphere>(Point{.x = -R, .y = 0, .z = -1}, R,
                                     material_left));
  world.add(std::make_unique<Sphere>(Point{.x = R, .y = 0, .z = -1}, R,
                                     material_right));

  if (!cam.render(world)) {
    return 1;
  }

  return 0;
}
