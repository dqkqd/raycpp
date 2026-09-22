#pragma once

#include <numbers>
#include <random>

inline double random_double() {
  static std::random_device r;
  static std::uniform_real_distribution<double> distribution(0.0, 1.0);
  static std::seed_seq seed({r(), r(), r(), r(), r(), r(), r(), r()});
  static std::mt19937 generator(seed);
  return distribution(generator);
}

inline double random_double(double min, double max) {
  return min + ((max - min) * random_double());
}

inline int random_int(int min, int max) {
  return static_cast<int>(random_double(min, max + 1));
}

inline double linear_to_gammar(double l) { return l > 0 ? sqrt(l) : 0; }

inline double degree_to_radian(double degree) {
  return degree * std::numbers::pi / 180;
}
