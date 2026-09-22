#include "image.hpp"
#include <algorithm>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <format>
#include <stdexcept>

Image::Image(const std::string &image_filename) {
  auto n = bytes_per_pixel;
  auto *raw = stbi_loadf(image_filename.c_str(), &image_width, &image_height,
                         &n, bytes_per_pixel);
  if (raw == nullptr) {
    throw std::runtime_error(
        std::format("Cannot load image {}", image_filename));
  }

  bytes_per_scanline = image_width * bytes_per_pixel;

  image_data = ImageData(raw);
}

[[nodiscard]] Color Image::data(int x, int y) const {
  x = std::clamp(x, 0, image_width - 1);
  y = std::clamp(y, 0, image_height - 1);
  auto offset = (y * bytes_per_scanline) + (x * bytes_per_pixel);
  return {.r = static_cast<double>(image_data[offset]),
          .g = static_cast<double>(image_data[offset + 1]),
          .b = static_cast<double>(image_data[offset + 2])};
}
