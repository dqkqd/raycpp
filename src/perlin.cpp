#include "perlin.hpp"
#include "utils.hpp"
#include "vec3.hpp"
#include <cmath>
#include <cstdint>

Perlin::Perlin() {
  for (int i = 0; i < point_count; i++) {
    randvec.at(i) = Vec3::random(-1, 1);
  }

  perlin_generate_perm(perm_x);
  perlin_generate_perm(perm_y);
  perlin_generate_perm(perm_z);
}

double Perlin::noise(const Point &p) const {
  auto u = p.x - std::floor(p.x);
  auto v = p.y - std::floor(p.y);
  auto w = p.z - std::floor(p.z);

  auto i = static_cast<uint32_t>(std::floor(p.x));
  auto j = static_cast<uint32_t>(std::floor(p.y));
  auto k = static_cast<uint32_t>(std::floor(p.z));

  std::array<Vec3, 8> c{};
  for (int di = 0; di < 2; di++) {
    for (int dj = 0; dj < 2; dj++) {
      for (int dk = 0; dk < 2; dk++) {
        c.at((di * 4) + (dj * 2) + dk) =
            randvec.at(perm_x.at((i + di) & 255U) ^ perm_y.at((j + dj) & 255U) ^
                       perm_z.at((k + dk) & 255U));
      }
    }
  }

  return perlin_interp(c, u, v, w);
}

double Perlin::turb(const Point &p, int depth) const {
  auto accum = 0.0;
  auto temp_p = p;
  auto weight = 1.0;
  for (int i = 0; i < depth; i++) {
    accum += weight * noise(temp_p);
    weight *= 0.5;
    temp_p = temp_p * 2;
  }
  return std::fabs(accum);
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

double Perlin::perlin_interp(std::array<Vec3, 8> c, double u, double v,
                             double w) {

  auto uu = u * u * (3 - 2 * u);
  auto vv = v * v * (3 - 2 * v);
  auto ww = w * w * (3 - 2 * w);

  auto accum = 0.0;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      for (int k = 0; k < 2; k++) {
        Vec3 weight_v(u - i, v - j, w - k);
        accum += ((i * uu) + ((1 - i) * (1 - uu))) *
                 ((j * vv) + ((1 - j) * (1 - vv))) *
                 ((k * ww) + ((1 - k) * (1 - ww))) *
                 c.at((4 * i) + (2 * j) + k).dot(weight_v);
      }
    }
  }
  return accum;
}
