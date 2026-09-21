#include <cstdint>
#include <format>
#include <ostream>

#include <color.h>

std::ostream &operator<<(std::ostream &os, const PrintableColor &c) {
  return os << std::format("{} {} {}\n", c.r, c.g, c.b);
}

PrintableColor Color::printable() const {
  auto ir = static_cast<uint8_t>(r * 255.999);
  auto ig = static_cast<uint8_t>(g * 255.999);
  auto ib = static_cast<uint8_t>(b * 255.999);
  return {.r = ir, .g = ig, .b = ib};
}
