#include "scenes.hpp"

int main() {
  int cs = 4;
  switch (cs) {
  case 1:
    return bouncing_spheres();
  case 2:
    return checker_spheres();
  case 3:
    return earth();
  case 4:
    return perlin_spheres();
  default:
    return 1;
  }
}
