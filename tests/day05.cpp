#include <aoc2025lib/day05.hpp>
#include <catch2/catch_test_macros.hpp>

namespace input {
static constexpr auto part01 =
    R"(3-5
10-14
16-20
12-18
9-21

1
5
8
11
17
32
)";
}

using namespace aoc2025::day05;

TEST_CASE("parts", "[day05]") {
  STATIC_CHECK(part01(input::part01) == 3);
  STATIC_CHECK(part02(input::part01) == 16);
}
TEST_CASE("parse_range", "[day05]") {
  STATIC_CHECK(parse_range("1-2") == Range{1, 2});
  STATIC_CHECK(parse_range("12-3") == Range{12, 3});
  STATIC_CHECK(parse_range("12-34") == Range{12, 34});
  STATIC_CHECK(parse_range("1-23") == Range{1, 23});
}
