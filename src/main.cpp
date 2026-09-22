#include "camera.hpp"
#include "color.hpp"
#include "material.hpp"
#include "point.hpp"
#include "sphere.hpp"
#include "utils.hpp"
#include "vec3.hpp"
#include "world.hpp"
#include <memory>

int main() {
  auto cam = Camera::init(
      16.0 / 9.0, 600, 100, 50, 20, Point{.x = 13, .y = 2, .z = 3},
      {.x = 0, .y = 0, .z = 0}, {.x = 0, .y = 1, .z = 0}, 0.6, 10.0);

  auto world = World();

  auto material_ground =
      std::make_shared<Lambertian>(Color{.r = 0.5, .g = 0.5, .b = 0.5});
  world.add(std::make_unique<Sphere>(Point{.x = 0, .y = -1000, .z = 0}, 1000,
                                     material_ground));

  for (int a = -11; a < 11; a++) {
    for (int b = -11; b < 11; b++) {
      auto choose_mat = random_double();
      Point center{.x = a + (0.9 * random_double()),
                   .y = 0.2,
                   .z = b + (0.9 * random_double())};
      if ((center - Point{.x = 4, .y = 0.2, .z = 0}).length() > 0.9) {
        if (choose_mat < 0.8) {
          auto albedo = Vec3::random() * Vec3::random();
          auto mat = std::make_shared<Lambertian>(
              Color{.r = albedo.x, .g = albedo.y, .b = albedo.z});
          world.add(std::make_unique<Sphere>(center, 0.2, mat));
        } else if (choose_mat < 0.95) {
          auto albedo = Vec3::random(0.5, 1);
          auto fuzz = random_double(0, 0.5);
          auto mat = std::make_shared<Metal>(
              Color{.r = albedo.x, .g = albedo.y, .b = albedo.z}, fuzz);
          world.add(std::make_unique<Sphere>(center, 0.2, mat));
        } else {
          auto mat = std::make_shared<Dielectrics>(1.5);
          world.add(std::make_unique<Sphere>(center, 0.2, mat));
        }
      }
    }
  }

  auto mat1 = std::make_shared<Dielectrics>(1.5);
  world.add(std::make_unique<Sphere>(Point{.x = 0, .y = 1, .z = 0}, 1, mat1));

  auto mat2 = std::make_shared<Lambertian>(Color{.r = 0.4, .g = 0.2, .b = 0.1});
  world.add(std::make_unique<Sphere>(Point{.x = -4, .y = 1, .z = 0}, 1, mat2));

  auto mat3 = std::make_shared<Metal>(Color{.r = 0.7, .g = 0.6, .b = 0.5}, 0);
  world.add(std::make_unique<Sphere>(Point{.x = 4, .y = 1, .z = 0}, 1, mat3));

  if (!cam.render(world)) {
    return 1;
  }

  return 0;
}
