#include "camera.hpp"
#include "point.hpp"
#include "sphere.hpp"
#include "world.hpp"
#include <memory>

int main() {
  auto cam = Camera::init(16.0 / 9.0, 400);

  auto world = World();
  world.add(std::make_unique<Sphere>(Point{.x = 0, .y = 0, .z = -1}, 0.5));
  world.add(std::make_unique<Sphere>(Point{.x = 0, .y = -100.5, .z = -1}, 100));

  if (!cam.render(world)) {
    return 1;
  }

  return 0;
}
