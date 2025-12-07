#include <aoc2025lib/day02.hpp>
#include <catch2/catch_test_macros.hpp>

namespace input {
static constexpr auto test
    = R"(11-22,95-115,998-1012,1188511880-1188511890,222220-222224,1698522-1698528,446443-446449,38593856-38593862,565653-565659,824824821-824824827,2121212118-2121212124)";
}

using namespace aoc2025::day02;

TEST_CASE("parts", "[day02]") {
  STATIC_CHECK(part01(input::test) == 1227775554);
  STATIC_CHECK(part02(input::test) == 4174379265);
}
