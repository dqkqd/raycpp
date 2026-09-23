#include "camera.hpp"
#include "color.hpp"
#include "hit.hpp"
#include "point.hpp"
#include "progress.hpp"
#include "ray.hpp"
#include "utils.hpp"
#include "vec3.hpp"
#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <format>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

Camera Camera::init(double aspect_ratio, int image_width, int samples_per_pixel,
                    int max_depth, double vfov, Point lookfrom, Point lookat,
                    Vec3 vup, double defocus_angle, double focus_dist,
                    Color background) {
  auto image_height = static_cast<int>(image_width / aspect_ratio);

  auto theta = degree_to_radian(vfov);
  auto h = std::tan(theta / 2);
  auto viewport_height = 2 * h * focus_dist;
  auto viewport_width = viewport_height * image_width / image_height;

  auto center = lookfrom;
  auto w = (lookfrom - lookat).unit();
  auto u = vup.cross(w);
  auto v = w.cross(u);

  auto viewport_u = viewport_width * u;
  auto viewport_v = viewport_height * -v;

  auto pixel_delta_u = viewport_u / image_width;
  auto pixel_delta_v = viewport_v / image_height;

  auto viewport_upper_left =
      center - focus_dist * w - viewport_u / 2 - viewport_v / 2;
  auto pixel00_loc =
      viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

  auto defocus_radius =
      focus_dist * std::tan(degree_to_radian(defocus_angle / 2));
  auto defocus_disk_u = u * defocus_radius;
  auto defocus_disk_v = v * defocus_radius;

  return {
      image_width,   image_height,  samples_per_pixel, 1.0 / samples_per_pixel,
      max_depth,     center,        pixel00_loc,       pixel_delta_u,
      pixel_delta_v, defocus_angle, defocus_disk_u,    defocus_disk_v,
      background};
}

Camera::Camera(int image_width, int image_height, int samples_per_pixel,
               double pixel_samples_scale, int max_depth, Point center,
               Point pixel00_loc, Vec3 pixel_delta_u, Vec3 pixel_delta_v,
               double defocus_angle, Vec3 defocus_disk_u, Vec3 defocus_disk_v,
               Color background)
    : image_width_(image_width), image_height_(image_height),
      samples_per_pixel_(samples_per_pixel),
      pixel_samples_scale_(pixel_samples_scale), max_depth_(max_depth),
      center_(center), pixel00_loc_(pixel00_loc), pixel_delta_u_(pixel_delta_u),
      pixel_delta_v_(pixel_delta_v), defocus_angle_(defocus_angle),
      defocus_disk_u_(defocus_disk_u), defocus_disk_v_(defocus_disk_v),
      background_(background) {}

bool Camera::render(const Hittable &world) const {

  std::array<bool, N_CHUNKS> results{};
  Progress progress(N_CHUNKS);
  auto start = std::chrono::high_resolution_clock::now();

  {
    std::vector<std::jthread> threads;
    threads.reserve(N_CHUNKS);
    for (int chunk = 0; chunk < N_CHUNKS; chunk++) {
      threads.emplace_back([&, chunk]() {
        results.at(chunk) = write_chunk(chunk, world, progress);
      });
    }
  }

  if (!std::ranges::all_of(results, std::identity{})) {
    return false;
  }

  auto result = merge_chunks();

  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
  std::clog << std::format("Done, in {}\n", duration);
  std::clog.flush();

  return result;
}

std::string Camera::image_chunk_name(int chunk) {
  return std::format("chunk_{}.ppm", chunk);
}

// write chunk of images
bool Camera::write_chunk(int chunk, const Hittable &world,
                         Progress &progress) const {
  std::ofstream chunk_file{image_chunk_name(chunk),
                           std::ofstream::trunc | std::ofstream::out};
  if (!chunk_file.is_open()) {
    return false;
  }
  auto chunk_size = image_height_ / N_CHUNKS;
  auto height_from = chunk * chunk_size;

  // the last chunk must contain all the height
  auto height_to =
      chunk == N_CHUNKS - 1 ? image_height_ : (chunk + 1) * chunk_size;

  for (int j = height_from; j < height_to; j++) {
    progress.update(chunk, std::format("chunk {}: {} scanlines remaining",
                                       chunk, height_to - j));
    for (int i = 0; i < image_width_; i++) {
      Color color = {.r = 0, .g = 0, .b = 0};
      for (int sample = 0; sample < samples_per_pixel_; sample++) {
        auto ray = sample_ray(i, j);
        color += ray_color(ray, world, max_depth_);
      }
      chunk_file << (color * pixel_samples_scale_).printable();
    }
  }

  progress.update(chunk, std::format("chunk {}: done", chunk));
  return true;
}

bool Camera::merge_chunks() const {
  std::ofstream file{"output.ppm", std::ofstream::trunc | std::ofstream::out};
  if (!file.is_open()) {
    return false;
  }
  file << std::format("P3\n{} {}\n255\n", image_width_, image_height_);

  for (int chunk = 0; chunk < N_CHUNKS; chunk++) {
    std::ifstream chunk_file{image_chunk_name(chunk), std::ifstream::in};
    if (!chunk_file.is_open()) {
      return false;
    }
    file << chunk_file.rdbuf();
  }

  return true;
}

Point Camera::defocus_disk_sample() const {
  auto v = Vec3::random_in_unit_disk();
  return center_ + (v.x * defocus_disk_u_) + (v.y * defocus_disk_v_);
}

Ray Camera::sample_ray(int i, int j) const {
  auto offsetx = random_double() - 0.5;
  auto offsety = random_double() - 0.5;

  auto pixel_sample = pixel00_loc_ + (i + offsetx) * pixel_delta_u_ +
                      (j + offsety) * pixel_delta_v_;
  auto ray_origin = defocus_angle_ <= 0 ? center_ : defocus_disk_sample();

  return {ray_origin, pixel_sample - ray_origin, random_double()};
}

Color Camera::ray_color(const Ray &ray, const Hittable &world,
                        int depth) const {
  static const Color black = {.r = 0, .g = 0, .b = 0};
  if (depth <= 0) {
    return black;
  }
  auto rec = world.hit(ray, {0.001, INFINITY});

  if (!rec.has_value()) {
    return background_;
  }

  auto color_from_emission =
      rec->material_->emitted(rec->coord_, rec->hit_point_);

  auto scatter = rec->material_->scatter(ray, *rec);
  if (!scatter.has_value()) {
    return color_from_emission;
  }

  auto color_from_scatter =
      scatter->attenuation * ray_color(scatter->scattered, world, depth - 1);

  return color_from_emission + color_from_scatter;
}

Color Camera::background_color(const Ray &ray) {
  auto unit = ray.direction_.unit();
  auto a = 0.5 * (unit.y + 1.0);
  static const Color c1 = {.r = 1, .g = 1, .b = 1};
  static const Color c2 = {.r = 0.5, .g = 0.7, .b = 1};
  return c1.lerp(c2, a);
}
