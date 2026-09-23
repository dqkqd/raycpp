#pragma once

#include "color.hpp"
#include "image.hpp"
#include "perlin.hpp"
#include "point.hpp"
#include <memory>
#include <string>

class TextureCoordinate {
public:
  double u, v;
};

class Texture {

public:
  Texture() = default;

  Texture(const Texture &) = default;
  Texture &operator=(const Texture &) = default;

  Texture(Texture &&) = delete;
  Texture &operator=(Texture &&) = delete;

  virtual ~Texture() = default;

  [[nodiscard]] virtual Color value(const TextureCoordinate &coord,
                                    const Point &p) const = 0;
};

class SolidColor : public Texture {
public:
  Color albedo_;

  explicit SolidColor(const Color &albedo);
  [[nodiscard]] Color value(const TextureCoordinate &coord,
                            const Point &p) const override;
};

class CheckerTexture : public Texture {
public:
  CheckerTexture(double scale, std::shared_ptr<Texture> even,
                 std::shared_ptr<Texture> odd);
  CheckerTexture(double scale, const Color &c1, const Color &c2);

  [[nodiscard]] Color value(const TextureCoordinate &coord,
                            const Point &p) const override;

private:
  double inv_scale;
  std::shared_ptr<Texture> even_;
  std::shared_ptr<Texture> odd_;
};

class ImageTexture : public Texture {
public:
  explicit ImageTexture(const std::string &filename);

  [[nodiscard]] Color value(const TextureCoordinate &coord,
                            const Point &p) const override;

private:
  Image image;
};

class NoiseTexture : public Texture {
public:
  explicit NoiseTexture(double scale);

  [[nodiscard]] Color value(const TextureCoordinate &coord,
                            const Point &p) const override;

private:
  Perlin noise;
  double scale_;
};
