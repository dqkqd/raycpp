#pragma once

#include "color.hpp"
#include "hit.hpp"
#include "point.hpp"
#include "sphere.hpp"
#include "vec3.hpp"
#include <optional>

class Ray {
public:
  Point origin;
  Vec3 direction;

  [[nodiscard]] Color color() const;

  [[nodiscard]] std::optional<HitRecord> hit(const Sphere &sphere) const;
  [[nodiscard]] Point at(double t) const;

private:
  [[nodiscard]] Color background_color() const;
};
