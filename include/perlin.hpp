#pragma once

#include "point.hpp"
#include <array>
#include <cstdint>

class Perlin {
public:
  Perlin();
  [[nodiscard]] double noise(const Point &p) const;

private:
  static constexpr int point_count = 256;

  std::array<double, point_count> randfloat{};
  std::array<std::uint8_t, point_count> perm_x{}, perm_y{}, perm_z{};

  static void perlin_generate_perm(std::array<std::uint8_t, point_count> &perm);
};
