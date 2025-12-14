#include <aoc2025lib/day11.hpp>
#include <catch2/catch_test_macros.hpp>

namespace input {
static constexpr auto part01 = R"(aaa: you hhh
you: bbb ccc
bbb: ddd eee
ccc: ddd eee fff
ddd: ggg
eee: out
fff: out
ggg: out
hhh: ccc fff iii
iii: out
)";

static constexpr auto part02 = R"(svr: aaa bbb
aaa: fft
fft: ccc
bbb: tty
tty: ccc
ccc: ddd eee
ddd: hub
hub: fff
eee: dac
dac: fff
fff: ggg hhh
ggg: out
hhh: out
)";
} // namespace input

using namespace aoc2025::day11;

TEST_CASE("parts", "[day11]") {
  // STATIC_CHECK(part01(input::part01) == 5);
  STATIC_CHECK(part02(input::part02) == 2);
}
// TEST_CASE("parse_line", "[day11]") {
//   STATIC_CHECK(parse_line("ddd: ggg") == Device{"ddd", {"ggg"}});
//   STATIC_CHECK(parse_line("ccc: ddd eee fff")
//                == Device{"ccc", {"ddd", "eee", "fff"}});
// }
