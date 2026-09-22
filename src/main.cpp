#include "scenes.hpp"

int main() {
  int cs = 2;
  switch (cs) {
  case 1:
    return bouncing_spheres();
  case 2:
    return checker_spheres();
  default:
    return 1;
  }
}
