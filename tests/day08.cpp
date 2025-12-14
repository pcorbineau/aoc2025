#include <aoc2025lib/day08.hpp>
#include <catch2/catch_test_macros.hpp>

namespace input {
static constexpr auto test = R"(162,817,812
57,618,57
906,360,560
592,479,940
352,342,300
466,668,158
542,29,236
431,825,988
739,650,466
52,470,668
216,146,977
819,987,18
117,168,530
805,96,715
346,949,466
970,615,88
941,993,340
862,61,35
984,92,344
425,690,689
)";
}

using namespace aoc2025::day08;

TEST_CASE("parts", "[day08]") {
  // STATIC_CHECK(part01(input::test) == 40);
  // STATIC_CHECK(part02(input::test) == 0);
}
TEST_CASE("parse_line", "[day08]") {
  STATIC_CHECK(parse_line("162,817,812") == Position{162, 817, 812});
}
