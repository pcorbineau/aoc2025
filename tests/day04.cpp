#include <aoc2025lib/day04.hpp>
#include <catch2/catch_test_macros.hpp>

namespace input {
static constexpr auto part01 =
    R"(..@@.@@@@.
@@@.@.@.@@
@@@@@.@.@@
@.@@@@..@.
@@.@@@@.@@
.@@@@@@@.@
.@.@.@.@@@
@.@@@.@@@@
.@@@@@@@@.
@.@.@@@.@.
)";
}

using namespace aoc2025::day04;

TEST_CASE("parts", "[day04]") {
  STATIC_CHECK(part01(input::part01) == 13);
  STATIC_CHECK(part02(input::part01) == 43);
}
