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
