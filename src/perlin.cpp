#include "perlin.hpp"
#include "utils.hpp"
#include <cstdint>

Perlin::Perlin() {
  for (int i = 0; i < point_count; i++) {
    randfloat.at(i) = random_double();
  }

  perlin_generate_perm(perm_x);
  perlin_generate_perm(perm_y);
  perlin_generate_perm(perm_z);
}

double Perlin::noise(const Point &p) const {
  std::uint8_t i = (static_cast<std::uint32_t>(4 * p.x)) & 255U;
  std::uint8_t j = (static_cast<std::uint32_t>(4 * p.y)) & 255U;
  std::uint8_t k = (static_cast<std::uint32_t>(4 * p.z)) & 255U;

  std::uint32_t iu = perm_x.at(i);
  std::uint32_t ju = perm_x.at(j);
  std::uint32_t ku = perm_x.at(k);
  return randfloat.at(iu ^ ju ^ ku);
}

void Perlin::perlin_generate_perm(std::array<std::uint8_t, point_count> &perm) {
  for (int i = 0; i < point_count; i++) {
    perm.at(i) = i;
  }

  for (int i = point_count - 1; i > 0; i--) {
    auto target = random_int(0, i);
    auto tmp = perm.at(i);
    perm.at(i) = perm.at(target);
    perm.at(target) = tmp;
  }
}
