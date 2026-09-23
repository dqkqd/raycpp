#include "quad.hpp"
#include "aabb.hpp"
#include "hit.hpp"
#include "interval.hpp"
#include "material.hpp"
#include "point.hpp"
#include "texture.hpp"
#include "vec3.hpp"
#include <memory>
#include <optional>
#include <utility>

Quad::Quad(Point Q, Vec3 u, Vec3 v, std::shared_ptr<Material> material)
    : Q(Q), u(u), v(v), material_(std::move(material)),
      bbox(AABB(Q, Q + u + v).merge(AABB(Q + u, Q + v))) {
  auto n = u.cross(v);
  normal = n.unit();
  D = normal.dot({.x = Q.x, .y = Q.y, .z = Q.z});
  w = n / n.dot(n);
}

AABB Quad::bounding_box() const { return bbox; }

std::optional<HitRecord> Quad::hit(const Ray &ray, Interval interval) const {
  auto denom = normal.dot(ray.direction_);
  if (std::fabs(denom) <= 1e-8) {
    return {};
  }

  auto nom =
      D -
      normal.dot({.x = ray.origin_.x, .y = ray.origin_.y, .z = ray.origin_.z});

  auto distance = nom / denom;
  if (!interval.contains(distance)) {
    return {};
  }

  auto hit_point = ray.at(distance);
  auto coord = texture_coordinate(hit_point - Q);
  if (!is_interior(coord.u, coord.v)) {
    return {};
  }

  return HitRecord(hit_point, ray.direction_, normal, distance, material_,
                   coord);
}

TextureCoordinate Quad::texture_coordinate(const Vec3 &p) const {
  auto alpha = w.dot(p.cross(v));
  auto beta = w.dot(u.cross(p));
  return {.u = alpha, .v = beta};
}

bool Quad::is_interior(double a, double b) {
  Interval unit = {0, 1};
  return unit.contains(a) && unit.contains(b);
}
