#include <cstdint>
#include <format>
#include <ostream>

#include "color.hpp"
#include "interval.hpp"
#include "utils.hpp"

Color Color::lerp(const Color &other, double a) const {
  return (1 - a) * *this + a * other;
}

Color operator*(const Color &c, double s) {
  return {.r = c.r * s, .g = c.g * s, .b = c.b * s};
}

Color operator*(double s, const Color &c) { return c * s; }

Color operator+(const Color &lhs, const Color &rhs) {
  return {.r = lhs.r + rhs.r, .g = lhs.g + rhs.g, .b = lhs.b + rhs.b};
}

Color operator*(const Color &lhs, const Color &rhs) {
  return {.r = lhs.r * rhs.r, .g = lhs.g * rhs.g, .b = lhs.b * rhs.b};
}

Color &Color::operator+=(const Color &other) {
  r += other.r;
  g += other.g;
  b += other.b;
  return *this;
}

PrintableColor Color::printable() const {
  static const Interval intensity{0.000, 0.999};
  auto ir = static_cast<uint8_t>(256 * intensity.clamp(linear_to_gammar(r)));
  auto ig = static_cast<uint8_t>(256 * intensity.clamp(linear_to_gammar(g)));
  auto ib = static_cast<uint8_t>(256 * intensity.clamp(linear_to_gammar(b)));
  return {.r = ir, .g = ig, .b = ib};
}

std::ostream &operator<<(std::ostream &os, const PrintableColor &c) {
  return os << std::format("{} {} {}\n", c.r, c.g, c.b);
}
