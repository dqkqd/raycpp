#pragma once

#include "color.hpp"
#include "ray.hpp"
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
  scatter(const Ray &ray, const HitRecord &rec) const = 0;
};

class Lambertian : public Material {
public:
  explicit Lambertian(Color albedo);

  [[nodiscard]] std::optional<Scatter>
  scatter(const Ray &ray, const HitRecord &rec) const override;

private:
  Color albedo_;
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
