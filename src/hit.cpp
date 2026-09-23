#include "hit.hpp"
#include "material.hpp"
#include "point.hpp"
#include "texture.hpp"
#include "vec3.hpp"
#include <memory>
#include <utility>

HitRecord::HitRecord(Point hit_point, Vec3 ray_direction, Vec3 normal,
                     double distance, std::shared_ptr<Material> material,
                     TextureCoordinate coord)
    : hit_point_(hit_point), distance_(distance),
      material_(std::move(material)), coord_(coord) {

  if (ray_direction.dot(normal) > 0) {
    direction_ = HitRecord::Direction::Inward;
    normal_ = -normal;
  } else {
    direction_ = HitRecord::Direction::Outward;
    normal_ = normal;
  }
}

bool Hittable::box_x_compare(const std::unique_ptr<Hittable> &lhs,
                             const std::unique_ptr<Hittable> &rhs) {
  return lhs->bounding_box().x.min < rhs->bounding_box().x.min;
}

bool Hittable::box_y_compare(const std::unique_ptr<Hittable> &lhs,
                             const std::unique_ptr<Hittable> &rhs) {
  return lhs->bounding_box().y.min < rhs->bounding_box().y.min;
}

bool Hittable::box_z_compare(const std::unique_ptr<Hittable> &lhs,
                             const std::unique_ptr<Hittable> &rhs) {
  return lhs->bounding_box().z.min < rhs->bounding_box().z.min;
}
