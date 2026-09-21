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
      auto r = i * 1.0 / (image_width - 1);
      auto g = j * 1.0 / (image_height - 1);
      auto b = 0.0;

      int ir = static_cast<int>(r * 255.999);
      int ig = static_cast<int>(g * 255.999);
      int ib = static_cast<int>(b * 255.999);

      file << std::format("{} {} {}\n", ir, ig, ib);
    }
  }

  std::clog << "\rDone                   \n";

  return 0;
}
