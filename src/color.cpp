#include <cstdint>
#include <format>
#include <ostream>

#include "color.hpp"

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

PrintableColor Color::printable() const {
  auto ir = static_cast<uint8_t>(r * 255.999);
  auto ig = static_cast<uint8_t>(g * 255.999);
  auto ib = static_cast<uint8_t>(b * 255.999);
  return {.r = ir, .g = ig, .b = ib};
}

std::ostream &operator<<(std::ostream &os, const PrintableColor &c) {
  return os << std::format("{} {} {}\n", c.r, c.g, c.b);
}
