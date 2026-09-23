#include "texture.hpp"
#include "color.hpp"
#include "image.hpp"
#include "interval.hpp"
#include "point.hpp"
#include <memory>
#include <utility>

SolidColor::SolidColor(const Color &albedo) : albedo_(albedo) {}

Color SolidColor::value(const TextureCoordinate & /*coord*/,
                        const Point & /*p*/) const {
  return albedo_;
}

CheckerTexture::CheckerTexture(double scale, std::shared_ptr<Texture> even,
                               std::shared_ptr<Texture> odd)
    : inv_scale(1.0 / scale), even_(std::move(even)), odd_(std::move(odd)) {}

CheckerTexture::CheckerTexture(double scale, const Color &c1, const Color &c2)
    : CheckerTexture(scale, std::make_shared<SolidColor>(c1),
                     std::make_shared<SolidColor>(c2)) {}

Color CheckerTexture::value(const TextureCoordinate &coord,
                            const Point &p) const {
  auto ix = static_cast<int>(inv_scale * p.x);
  auto iy = static_cast<int>(inv_scale * p.y);
  auto iz = static_cast<int>(inv_scale * p.z);
  auto is_even = (ix + iy + iz) % 2 == 0;
  return is_even ? even_->value(coord, p) : odd_->value(coord, p);
}

ImageTexture::ImageTexture(const std::string &filename) : image{filename} {}

Color ImageTexture::value(const TextureCoordinate &coord,
                          const Point & /*p*/) const {
  if (image.height() <= 0) {
    return {.r = 0, .g = 1, .b = 1};
  }
  auto u = Interval(0, 1).clamp(coord.u);
  auto v = 1 - Interval(0, 1).clamp(coord.v);
  auto i = static_cast<int>(u * image.width());
  auto j = static_cast<int>(v * image.height());
  return image.data(i, j);
}

NoiseTexture::NoiseTexture(double scale) : scale_(scale) {}

Color NoiseTexture::value(const TextureCoordinate & /*coord*/,
                          const Point &p) const {
  return Color{.r = 1, .g = 1, .b = 1} * noise.noise(p * scale_);
}
