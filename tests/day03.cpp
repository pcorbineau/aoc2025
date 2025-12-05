#include <aoc2025lib/day03.hpp>
#include <catch2/catch_test_macros.hpp>

namespace input {
static constexpr auto part01 =
    R"(987654321111111
811111111111119
234234234234278
818181911112111
)";
}

using namespace aoc2025::day03;

TEST_CASE("parts", "[day03]") {
  STATIC_CHECK(part01(input::part01) == 357);
  STATIC_CHECK(part02(input::part01) == 3121910778619);
}
TEST_CASE("largest_joltage_p01", "[day03]") {
  STATIC_CHECK(largest_joltage(2, "987654321111111") == 98);
  STATIC_CHECK(largest_joltage(2, "811111111111119") == 89);
  STATIC_CHECK(largest_joltage(2, "234234234234278") == 78);
  STATIC_CHECK(largest_joltage(2, "818181911112111") == 92);
}
TEST_CASE("largest_joltage_p02", "[day03]") {
  STATIC_CHECK(largest_joltage(12, "987654321111111") == 987654321111);
  STATIC_CHECK(largest_joltage(12, "811111111111119") == 811111111119);
  STATIC_CHECK(largest_joltage(12, "234234234234278") == 434234234278);
  STATIC_CHECK(largest_joltage(12, "818181911112111") == 888911112111);
}
