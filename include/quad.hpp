#pragma once

#include "aabb.hpp"
#include "hit.hpp"
#include "material.hpp"
#include "point.hpp"
#include "texture.hpp"
#include "vec3.hpp"
#include <memory>
#include <optional>

class Quad : public Hittable {
public:
  Quad(Point Q, Vec3 u, Vec3 v, std::shared_ptr<Material> material);

  [[nodiscard]] std::optional<HitRecord> hit(const Ray &ray,
                                             Interval interval) const override;

  [[nodiscard]] AABB bounding_box() const override;

  [[nodiscard]] TextureCoordinate texture_coordinate(const Vec3 &p) const;

  static bool is_interior(double a, double b);

private:
  Point Q_;
  Vec3 u_, v_;
  Vec3 w{};
  std::shared_ptr<Material> material_;
  Vec3 normal{};
  double D{};
  AABB bbox = AABB::empty();
};
