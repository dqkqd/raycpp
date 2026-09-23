#include "scenes.hpp"

int main() {
  const int cs = 8;
  switch (cs) {
  case 1:
    return bouncing_spheres();
  case 2:
    return checker_spheres();
  case 3:
    return earth();
  case 4:
    return perlin_spheres();
  case 5:
    return quads();
  case 6:
    return simple_light();
  case 7:
    return cornell_box();
  case 8:
    return cornell_smoke();
  default:
    return 1;
  }
}
