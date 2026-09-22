#include "scenes.hpp"

int main() {
  int cs = 3;
  switch (cs) {
  case 1:
    return bouncing_spheres();
  case 2:
    return checker_spheres();
  case 3:
    return earth();
  default:
    return 1;
  }
}
