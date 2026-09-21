#include "color.hpp"
#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include <sstream>

TEST_CASE("Color is scaled when print") {
  const Color c = {.r = 0.1, .g = 0.2, .b = 0.3};
  const PrintableColor pc = c.printable();
  REQUIRE(pc.r == 25);
  REQUIRE(pc.g == 51);
  REQUIRE(pc.b == 76);

  std::ostringstream os;
  os << pc;
  REQUIRE(os.str() == "25 51 76\n");
}

TEST_CASE("color + color") {
  const Color c1 = {.r = 0.1, .g = 0.2, .b = 0.3};
  const Color c2 = {.r = 0.4, .g = 0.5, .b = 0.6};
  auto res = c1 + c2;
  REQUIRE(res.r == Catch::Approx(0.5));
  REQUIRE(res.g == Catch::Approx(0.7));
  REQUIRE(res.b == Catch::Approx(0.9));
}

TEST_CASE("color * double") {
  const Color c = {.r = 0.1, .g = 0.2, .b = 0.3};

  auto res = c * 2;
  REQUIRE(res.r == Catch::Approx(0.2));
  REQUIRE(res.g == Catch::Approx(0.4));
  REQUIRE(res.b == Catch::Approx(0.6));

  res = 2 * c;
  REQUIRE(res.r == Catch::Approx(0.2));
  REQUIRE(res.g == Catch::Approx(0.4));
  REQUIRE(res.b == Catch::Approx(0.6));
}

TEST_CASE("color lerp") {
  const Color c1 = {.r = 0.1, .g = 0.2, .b = 0.3};
  const Color c2 = {.r = 0.4, .g = 0.5, .b = 0.6};
  auto res = c1.lerp(c2, 0.3);
  REQUIRE(res.r == 0.19);
  REQUIRE(res.g == 0.29);
  REQUIRE(res.b == 0.39);
}
