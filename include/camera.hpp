#pragma once

#include "color.hpp"
#include "hit.hpp"
#include "point.hpp"
#include "vec3.hpp"

class Camera {
public:
  static Camera init(double aspect_ratio, int image_width,
                     int samples_per_pixel, int max_depth);

  [[nodiscard]] bool render(const Hittable &world) const;

private:
  int image_width_;
  int image_height_;

  int samples_per_pixel_;
  double pixel_samples_scale_;

  int max_depth_;

  Point center_;
  Point pixel00_loc_;
  Vec3 pixel_delta_u_;
  Vec3 pixel_delta_v_;

  Camera(int image_width, int image_height, int samples_per_pixel,
         double pixel_samples_scale, int max_depth, Point center,
         Point pixel00_loc, Vec3 pixel_delta_u, Vec3 pixel_delta_v);

  [[nodiscard]] static Color ray_color(const Ray &ray, const Hittable &world,
                                       int depth);
  [[nodiscard]] static Color background_color(const Ray &ray);

  [[nodiscard]] Ray sample_ray(int i, int j) const;
};
