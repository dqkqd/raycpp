#include "perlin.hpp"
#include "utils.hpp"
#include <cmath>
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
  auto u = p.x - std::floor(p.x);
  auto v = p.y - std::floor(p.y);
  auto w = p.z - std::floor(p.z);
  u = u * u * (3 - 2 * u);
  v = v * v * (3 - 2 * v);
  w = w * w * (3 - 2 * w);

  auto i = static_cast<uint32_t>(std::floor(p.x));
  auto j = static_cast<uint32_t>(std::floor(p.y));
  auto k = static_cast<uint32_t>(std::floor(p.z));

  std::array<double, 8> c{};
  for (int di = 0; di < 2; di++) {
    for (int dj = 0; dj < 2; dj++) {
      for (int dk = 0; dk < 2; dk++) {
        c.at((di * 4) + (dj * 2) + dk) = randfloat.at(
            perm_x.at((i + di) & 255U) ^ perm_y.at((j + dj) & 255U) ^
            perm_z.at((k + dk) & 255U));
      }
    }
  }

  return trilinear_interp(c, u, v, w);
}

void Perlin::perlin_generate_perm(
    std::array<std::uint32_t, point_count> &perm) {
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

double Perlin::trilinear_interp(std::array<double, 8> c, double u, double v,
                                double w) {

  auto accum = 0.0;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      for (int k = 0; k < 2; k++) {
        accum += ((i * u) + ((1 - i) * (1 - u))) *
                 ((j * v) + ((1 - j) * (1 - v))) *
                 ((k * w) + ((1 - k) * (1 - w))) * c.at((4 * i) + (2 * j) + k);
      }
    }
  }
  return accum;
}
