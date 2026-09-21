#include "point.hpp"
#include "vec3.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("point - point") {
  const Point p1 = {.x = 1, .y = 2, .z = 3};
  const Point p2 = {.x = 3, .y = 5, .z = 7};
  REQUIRE(p2 - p1 == (Vec3){2, 3, 4});
  REQUIRE(p1 - p2 == (Vec3){-2, -3, -4});
}

TEST_CASE("point + vec3") {
  const Point p = {.x = 1, .y = 2, .z = 3};
  const Vec3 v = {.x = 2, .y = 4, .z = 6};
  auto res = p + v;
  REQUIRE(res.x == 3);
  REQUIRE(res.y == 6);
  REQUIRE(res.z == 9);
}

TEST_CASE("point - Vec3") {
  const Point p = {.x = 1, .y = 2, .z = 3};
  const Vec3 v = {.x = 2, .y = 4, .z = 6};
  auto res = p - v;
  REQUIRE(res.x == -1);
  REQUIRE(res.y == -2);
  REQUIRE(res.z == -3);
}
