#include "scenes.hpp"

int main() {
  const int cs = 5;
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
  default:
    return 1;
  }
}
