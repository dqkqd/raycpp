#include "vec3.hpp"
#include <catch2/catch_test_macros.hpp>
#include <cmath>

TEST_CASE("vec3 * double") {
  const Vec3 v = {.x = 1, .y = 2, .z = 3};
  REQUIRE(v * 2 == (Vec3){2, 4, 6});
  REQUIRE(2 * v == (Vec3){2, 4, 6});
}

TEST_CASE("vec3 / double") {
  const Vec3 v = {.x = 2, .y = 4, .z = 6};
  REQUIRE(v / 2 == (Vec3){1, 2, 3});
}

TEST_CASE("vec3 + vec3") {
  const Vec3 v1 = {.x = 1, .y = 2, .z = 3};
  const Vec3 v2 = {.x = 2, .y = 4, .z = 6};
  REQUIRE(v1 + v2 == (Vec3){3, 6, 9});
}

TEST_CASE("vec3 length square") {
  const Vec3 v = {.x = 1, .y = 2, .z = 3};
  REQUIRE(v.length_square() == 14);
}

TEST_CASE("vec3 length") {
  const Vec3 v = {.x = 1, .y = 2, .z = 3};
  REQUIRE(v.length() == sqrt(14));
}

TEST_CASE("vec3 unit") {
  const Vec3 v = {.x = 1, .y = 2, .z = 3};
  REQUIRE(v.unit() == (Vec3){1 / sqrt(14), 2 / sqrt(14), 3 / sqrt(14)});
}
