#include "hit.hpp"
#include "material.hpp"
#include "point.hpp"
#include "vec3.hpp"
#include <memory>
#include <utility>

HitRecord::HitRecord(Point hit_point, Direction direction, Vec3 normal,
                     double distance, std::shared_ptr<Material> material)
    : hit_point_(hit_point), direction_(direction), normal_(normal),
      distance_(distance), material_(std::move(material)) {}

bool Hittable::box_x_compare(const std::unique_ptr<Hittable> &lhs,
                             const std::unique_ptr<Hittable> &rhs) {
  return lhs->bounding_box().x.tmin < rhs->bounding_box().x.tmin;
}

bool Hittable::box_y_compare(const std::unique_ptr<Hittable> &lhs,
                             const std::unique_ptr<Hittable> &rhs) {
  return lhs->bounding_box().y.tmin < rhs->bounding_box().y.tmin;
}

bool Hittable::box_z_compare(const std::unique_ptr<Hittable> &lhs,
                             const std::unique_ptr<Hittable> &rhs) {
  return lhs->bounding_box().z.tmin < rhs->bounding_box().z.tmin;
}
