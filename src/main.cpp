#include "color.h"
#include <fstream>
#include <iostream>

int main() {
  std::string filename{"output.ppm"};
  std::ofstream file{filename, std::ofstream::trunc | std::ofstream::out};

  auto image_width = 256;
  auto image_height = 256;
  file << std::format("P3\n{} {}\n255\n", image_width, image_height);

  for (int j = 0; j < image_height; j++) {
    std::clog << std::format("\rScanlines remaining: ", image_height - j);
    for (int i = 0; i < image_width; i++) {
      Color c = {
          .r = i * 1.0 / (image_width - 1),
          .g = j * 1.0 / (image_height - 1),
          .b = 0.0,
      };

      file << c.printable();
    }
  }

  std::clog << "\rDone                   \n";

  return 0;
}
