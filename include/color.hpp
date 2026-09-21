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

  [[nodiscard]] Color lerp(const Color &other, double a) const;

  friend Color operator*(const Color &c, double s);
  friend Color operator*(double s, const Color &c);
  friend Color operator+(const Color &lhs, const Color &rhs);

  Color &operator+=(const Color &other);

  [[nodiscard]] PrintableColor printable() const;
};
