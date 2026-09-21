#pragma once

#include "color.hpp"
#include "hit.hpp"
#include "point.hpp"
#include "vec3.hpp"

class Camera {
public:
  static Camera init(double aspect_ratio, int image_width);

  [[nodiscard]] bool render(const Hittable &world) const;

private:
  int image_width_;
  int image_height_;

  Point center_;
  Point pixel00_loc_;
  Vec3 pixel_delta_u_;
  Vec3 pixel_delta_v_;

  Camera(int image_width, int image_height, Point center, Point pixel00_loc,
         Vec3 pixel_delta_u, Vec3 pixel_delta_v);

  [[nodiscard]] static Color color(const Ray &ray, const Hittable &world);
  [[nodiscard]] static Color background_color(const Ray &ray);
};
