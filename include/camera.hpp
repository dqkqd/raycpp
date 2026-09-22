#pragma once

#include "color.hpp"
#include "hit.hpp"
#include "point.hpp"
#include "vec3.hpp"
#include <string>

class Camera {
public:
  static Camera init(double aspect_ratio, int image_width,
                     int samples_per_pixel, int max_depth, double vfov,
                     Point lookfrom, Point lookat, Vec3 vup,
                     double defocus_angle, double focus_dist);

  [[nodiscard]] bool render(const Hittable &world) const;

private:
  static const int N_CHUNKS = 2;

  int image_width_;
  int image_height_;

  int samples_per_pixel_;
  double pixel_samples_scale_;

  int max_depth_;

  Point center_;
  Point pixel00_loc_;
  Vec3 pixel_delta_u_;
  Vec3 pixel_delta_v_;

  double defocus_angle_;
  Vec3 defocus_disk_u_;
  Vec3 defocus_disk_v_;

  Camera(int image_width, int image_height, int samples_per_pixel,
         double pixel_samples_scale, int max_depth, Point center,
         Point pixel00_loc, Vec3 pixel_delta_u, Vec3 pixel_delta_v,
         double defocus_angle, Vec3 defocus_disk_u, Vec3 defocus_disk_v);

  [[nodiscard]] static Color ray_color(const Ray &ray, const Hittable &world,
                                       int depth);
  [[nodiscard]] static Color background_color(const Ray &ray);

  [[nodiscard]] Ray sample_ray(int i, int j) const;
  [[nodiscard]] Point defocus_disk_sample() const;

  // image chunk name
  static std::string image_chunk_name(int chunk);
  // write image from height_from to height_to
  [[nodiscard]] bool write_chunk(int chunk, const Hittable &world) const;
  // merge all chunked images into the final one
  [[nodiscard]] bool merge_chunks() const;
};
