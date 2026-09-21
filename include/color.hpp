#pragma once

#include <cstdint>
#include <ostream>

class PrintableColor {
public:
  uint8_t r, g, b;
  friend std::ostream &operator<<(std::ostream &os, const PrintableColor &c);
};

class Color {
public:
  double r, g, b;
  [[nodiscard]] PrintableColor printable() const;
};
