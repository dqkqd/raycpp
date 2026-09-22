#pragma once

#include <memory>
#include <string>

#include "color.hpp"
#include "stb_image.h"

struct StbFree {
  void operator()(float *p) { stbi_image_free(p); }
};

using ImageData = std::unique_ptr<float[], StbFree>; // NOLINT

class Image {
public:
  explicit Image(const std::string &image_filename);

  [[nodiscard]] Color data(int x, int y) const;

  [[nodiscard]] int width() const { return image_width; }
  [[nodiscard]] int height() const { return image_height; }

private:
  int bytes_per_pixel = 3;
  int image_width = 0;
  int image_height = 0;
  int bytes_per_scanline = 0;

  ImageData image_data;
};
