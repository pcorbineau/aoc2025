#include <aoc2025lib/day09.hpp>
#include <catch2/catch_test_macros.hpp>

namespace input {
static constexpr auto test = R"(7,1
11,1
11,7
9,7
9,5
2,5
2,3
7,3
)";
}

using namespace aoc2025::day09;

TEST_CASE("parts", "[day09]") {
  STATIC_CHECK(part01(input::test) == 50);
  // STATIC_CHECK(part02(input::test) == 0);
}
