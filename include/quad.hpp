#pragma once

#include "aabb.hpp"
#include "hit.hpp"
#include "material.hpp"
#include "point.hpp"
#include "texture.hpp"
#include "vec3.hpp"
#include "world.hpp"
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

inline std::unique_ptr<World> box(const Point &a, const Point &b,
                                  const std::shared_ptr<Material> &material) {
  auto sides = std::make_unique<World>();

  Point min = {.x = std::fmin(a.x, b.x),
               .y = std::min(a.y, b.y),
               .z = std::min(a.z, b.z)};
  Point max = {.x = std::fmax(a.x, b.x),
               .y = std::max(a.y, b.y),
               .z = std::max(a.z, b.z)};

  Vec3 dx = {.x = max.x - min.x, .y = 0, .z = 0};
  Vec3 dy = {.x = 0, .y = max.y - min.y, .z = 0};
  Vec3 dz = {.x = 0, .y = 0, .z = max.z - min.z};

  sides->add(std::make_unique<Quad>(Point{.x = min.x, .y = min.y, .z = max.z},
                                    dx, dy, material));
  sides->add(std::make_unique<Quad>(Point{.x = max.x, .y = min.y, .z = max.z},
                                    -dz, dy, material));
  sides->add(std::make_unique<Quad>(Point{.x = max.x, .y = min.y, .z = min.z},
                                    -dx, dy, material));
  sides->add(std::make_unique<Quad>(Point{.x = min.x, .y = min.y, .z = min.z},
                                    dz, dy, material));
  sides->add(std::make_unique<Quad>(Point{.x = min.x, .y = max.y, .z = max.z},
                                    dx, -dz, material));
  sides->add(std::make_unique<Quad>(Point{.x = min.x, .y = max.y, .z = min.z},
                                    dx, dz, material));

  return sides;
}
