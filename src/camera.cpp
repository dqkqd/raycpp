#include "camera.hpp"
#include "ray.hpp"
#include "utils.h"
#include "vec3.hpp"
#include <cmath>
#include <fstream>
#include <iostream>

Camera Camera::init(double aspect_ratio, int image_width,
                    int samples_per_pixel) {
  auto image_height = static_cast<int>(image_width / aspect_ratio);
  auto focal_length = 1.0;
  auto viewport_height = 2.0;
  auto viewport_width = viewport_height * image_width / image_height;

  auto center = Point{.x = 0, .y = 0, .z = 0};

  auto viewport_u = Vec3{.x = viewport_width, .y = 0, .z = 0};
  auto viewport_v = Vec3{.x = 0, .y = -viewport_height, .z = 0};

  auto pixel_delta_u = viewport_u / image_width;
  auto pixel_delta_v = viewport_v / image_height;

  auto viewport_upper_left = center - Vec3{.x = 0, .y = 0, .z = focal_length} -
                             viewport_u / 2 - viewport_v / 2;
  auto pixel00_loc =
      viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

  return {image_width, image_height, samples_per_pixel, 1.0 / samples_per_pixel,
          center,      pixel00_loc,  pixel_delta_u,     pixel_delta_v};
}

Camera::Camera(int image_width, int image_height, int samples_per_pixel,
               double pixel_samples_scale, Point center, Point pixel00_loc,
               Vec3 pixel_delta_u, Vec3 pixel_delta_v)
    : image_width_(image_width), image_height_(image_height),
      samples_per_pixel_(samples_per_pixel),
      pixel_samples_scale_(pixel_samples_scale), center_(center),
      pixel00_loc_(pixel00_loc), pixel_delta_u_(pixel_delta_u),
      pixel_delta_v_(pixel_delta_v) {}

bool Camera::render(const Hittable &world) const {
  const std::string filename{"output.ppm"};
  std::ofstream file{filename, std::ofstream::trunc | std::ofstream::out};
  if (!file.is_open()) {
    return false;
  }

  file << std::format("P3\n{} {}\n255\n", image_width_, image_height_);

  for (int j = 0; j < image_height_; j++) {
    std::clog << std::format("\rScanlines remaining: ", image_height_ - j);
    for (int i = 0; i < image_width_; i++) {
      Color color = {.r = 0, .g = 0, .b = 0};
      for (int sample = 0; sample < samples_per_pixel_; sample++) {
        auto ray = sample_ray(i, j);
        color += ray_color(ray, world);
      }
      file << (color * pixel_samples_scale_).printable();
    }
  }

  std::clog << "\rDone                   \n";
  return true;
}

Ray Camera::sample_ray(int i, int j) const {
  auto offsetx = random_double();
  auto offsety = random_double();

  auto pixel_sample = pixel00_loc_ + (i + offsetx) * pixel_delta_u_ +
                      (j + offsety) * pixel_delta_v_;
  auto ray_origin = center_;

  return {.origin = ray_origin, .direction = pixel_sample - ray_origin};
}

Color Camera::ray_color(const Ray &ray, const Hittable &world) {
  auto rec = world.hit(ray, {.tmin = 0.001, .tmax = INFINITY});
  if (rec.has_value()) {
    auto unit_normal = rec->normal_;
    Color c = {.r = unit_normal.x, .g = unit_normal.y, .b = unit_normal.z};
    return c.lerp({.r = 1, .g = 1, .b = 1}, 0.5);
  }
  return background_color(ray);
}

Color Camera::background_color(const Ray &ray) {
  auto unit = ray.direction.unit();
  auto a = 0.5 * (unit.y + 1.0);
  Color c1 = {.r = 1, .g = 1, .b = 1};
  Color c2 = {.r = 0.5, .g = 0.7, .b = 1};
  return c1.lerp(c2, a);
}
