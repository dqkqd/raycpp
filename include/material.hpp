#pragma once

#include "color.hpp"
#include "point.hpp"
#include "ray.hpp"
#include "texture.hpp"
#include <cmath>
#include <memory>
#include <optional>

class HitRecord;

class Scatter {
public:
  Ray scattered;
  Color attenuation;
};

class Material {
public:
  Material() = default;
  Material(const Material &) = delete;
  Material(Material &&) = delete;
  Material &operator=(const Material &) = delete;
  Material &operator=(Material &&) = delete;
  virtual ~Material() = default;

  [[nodiscard]] virtual std::optional<Scatter>
  scatter(const Ray & /*ray*/, const HitRecord & /*rec*/) const {
    return {};
  };

  [[nodiscard]] virtual Color emitted(const TextureCoordinate & /*coord*/,
                                      const Point & /*p*/) const {
    return {.r = 0, .g = 0, .b = 0};
  }
};

class Lambertian : public Material {
public:
  explicit Lambertian(const Color &color);
  explicit Lambertian(std::shared_ptr<Texture> tex);

  [[nodiscard]] std::optional<Scatter>
  scatter(const Ray &ray, const HitRecord &rec) const override;

private:
  std::shared_ptr<Texture> tex_;
};

class Metal : public Material {
public:
  explicit Metal(Color albedo, double fuzz);

  [[nodiscard]] std::optional<Scatter>
  scatter(const Ray &ray, const HitRecord &rec) const override;

private:
  Color albedo_;
  double fuzz_;
};

class Dielectrics : public Material {
public:
  explicit Dielectrics(double refraction_index);

  [[nodiscard]] std::optional<Scatter>
  scatter(const Ray &ray, const HitRecord &rec) const override;

private:
  double refraction_index_;
  // Schlick's approximation
  static double refelectance(double cosine, double refraction_index) {
    auto r0 = (1 - refraction_index) / (1 + refraction_index);
    r0 = r0 * r0;
    return r0 + ((1 - r0) * std::pow(1 - cosine, 5));
  }
};

class DiffuseLight : public Material {
public:
  explicit DiffuseLight(std::shared_ptr<Texture> tex);
  explicit DiffuseLight(const Color &emit);

  [[nodiscard]] Color emitted(const TextureCoordinate &coord,
                              const Point &p) const override;

private:
  std::shared_ptr<Texture> tex_;
};

class Isotropic : public Material {
public:
  explicit Isotropic(std::shared_ptr<Texture> tex);
  explicit Isotropic(const Color &albedo);

  [[nodiscard]] std::optional<Scatter>
  scatter(const Ray &ray, const HitRecord &rec) const override;

private:
  std::shared_ptr<Texture> tex_;
};
