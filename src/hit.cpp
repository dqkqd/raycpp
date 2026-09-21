#include "hit.hpp"
#include "point.hpp"
#include "vec3.hpp"

HitRecord::HitRecord(Point hit_point, Direction direction, Vec3 normal,
                     double distance)
    : hit_point_(hit_point), direction_(direction), normal_(normal),
      distance_(distance) {}
