#include "camera.hpp"
#include "material.hpp"
#include "point.hpp"
#include "sphere.hpp"
#include "world.hpp"
#include <memory>

int main() {
  auto cam = Camera::init(16.0 / 9.0, 400, 100, 50);

  auto world = World();

  auto material_ground =
      std::make_shared<Lambertian>(Color{.r = 0.8, .g = 0.8, .b = 0});
  auto material_center =
      std::make_shared<Lambertian>(Color{.r = 0.1, .g = 0.2, .b = 0.5});
  auto material_left =
      std::make_shared<Metal>(Color{.r = 0.8, .g = 0.8, .b = 0.8});
  auto material_right =
      std::make_shared<Metal>(Color{.r = 0.8, .g = 0.6, .b = 0.2});

  world.add(std::make_unique<Sphere>(Point{.x = 0, .y = -100.5, .z = -1}, 100,
                                     material_ground));
  world.add(std::make_unique<Sphere>(Point{.x = 0, .y = 0, .z = -1.2}, 0.5,
                                     material_center));
  world.add(std::make_unique<Sphere>(Point{.x = -1.0, .y = 0, .z = -1.0}, 0.5,
                                     material_left));
  world.add(std::make_unique<Sphere>(Point{.x = 1.0, .y = 0, .z = -1.0}, 0.5,
                                     material_right));

  if (!cam.render(world)) {
    return 1;
  }

  return 0;
}
