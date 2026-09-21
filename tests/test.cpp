#include "color.hpp"
#include <catch2/catch_test_macros.hpp>

#include <sstream>

TEST_CASE("Factorials are computed", "[factorial]") {
  const Color c = {.r = 0.1, .g = 0.2, .b = 0.3};
  const PrintableColor pc = c.printable();
  REQUIRE(pc.r == 25);
  REQUIRE(pc.g == 51);
  REQUIRE(pc.b == 76);

  std::ostringstream os;
  os << pc;
  REQUIRE(os.str() == "25 51 76\n");
}
