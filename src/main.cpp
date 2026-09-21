#include "color.hpp"
#include "point.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "vec3.hpp"
#include "world.hpp"
#include <format>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>

int main() {
  const std::string filename{"output.ppm"};
  std::ofstream file{filename, std::ofstream::trunc | std::ofstream::out};

  auto aspect_ratio = 16.0 / 9;
  auto image_width = 400;
  auto image_height = image_width / aspect_ratio;

  auto focal_length = 1.0;
  auto viewport_height = 2.0;
  auto viewport_width = viewport_height * image_width / image_height;

  auto camera_center = Point{.x = 0, .y = 0, .z = 0};
  auto viewport_u = Vec3{.x = viewport_width, .y = 0, .z = 0};
  auto viewport_v = Vec3{.x = 0, .y = -viewport_height, .z = 0};

  auto pixel_delta_u = viewport_u / image_width;
  auto pixel_delta_v = viewport_v / image_height;

  auto viewport_upper_left = camera_center -
                             Vec3{.x = 0, .y = 0, .z = focal_length} -
                             viewport_u / 2 - viewport_v / 2;
  auto pixel00_loc =
      viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

  file << std::format("P3\n{} {}\n255\n", image_width, image_height);

  auto world = World();
  world.add(std::make_unique<Sphere>(Point{.x = 0, .y = 0, .z = -1}, 0.5));
  world.add(std::make_unique<Sphere>(Point{.x = 0, .y = -100.5, .z = -1}, 100));

  for (int j = 0; j < image_height; j++) {
    std::clog << std::format("\rScanlines remaining: ", image_height - j);
    for (int i = 0; i < image_width; i++) {
      auto pixcel_center =
          pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
      auto ray_direction = pixcel_center - camera_center;
      auto ray = Ray{.origin = camera_center, .direction = ray_direction};
      file << ray.color(world).printable();
    }
  }

  std::clog << "\rDone                   \n";

  return 0;
}
