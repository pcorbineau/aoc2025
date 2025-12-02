#include <aoc2025lib/day01.hpp>
#include <catch2/catch_test_macros.hpp>
#include <format>

namespace input {
static constexpr auto part01 = R"(L68
L30
R48
L5
R60
L55
L1
L99
R14
L82)";
}

using namespace aoc2025::day01;

namespace Catch {
template <> struct StringMaker<ComputeResult> {
  static std::string convert(const ComputeResult &res) {
    return std::format("[ {}, {} ]", res.value, res.passes0);
  }
};
} // namespace Catch

TEST_CASE("parts", "[day01]") {
  STATIC_CHECK(part01(input::part01) == 3);
  STATIC_CHECK(part02(input::part01) == 6);
}

TEST_CASE("rotate", "[day01]") {
  STATIC_CHECK(rotate({Rotation::Direction::Left, 68}, 50) ==
               ComputeResult{82, 1});
  STATIC_CHECK(rotate({Rotation::Direction::Left, 30}, 82) ==
               ComputeResult{52, 0});
  STATIC_CHECK(rotate({Rotation::Direction::Right, 48}, 52) ==
               ComputeResult{0, 1});
  STATIC_CHECK(rotate({Rotation::Direction::Left, 5}, 0) ==
               ComputeResult{95, 0});
  STATIC_CHECK(rotate({Rotation::Direction::Right, 60}, 95) ==
               ComputeResult{55, 1});
  STATIC_CHECK(rotate({Rotation::Direction::Left, 55}, 55) ==
               ComputeResult{0, 1});
  STATIC_CHECK(rotate({Rotation::Direction::Left, 1}, 0) ==
               ComputeResult{99, 0});
  STATIC_CHECK(rotate({Rotation::Direction::Left, 99}, 99) ==
               ComputeResult{0, 1});
  STATIC_CHECK(rotate({Rotation::Direction::Right, 14}, 0) ==
               ComputeResult{14, 0});
  STATIC_CHECK(rotate({Rotation::Direction::Left, 82}, 14) ==
               ComputeResult{32, 1});

  // Special cases
  STATIC_CHECK(rotate({Rotation::Direction::Right, 1000}, 50) ==
               ComputeResult{50, 10});
  STATIC_CHECK(rotate({Rotation::Direction::Left, 50}, 50) ==
               ComputeResult{0, 1});
  STATIC_CHECK(rotate({Rotation::Direction::Right, 101}, 0) ==
               ComputeResult{1, 1});
  STATIC_CHECK(rotate({Rotation::Direction::Right, 400}, 0) ==
               ComputeResult{0, 4});
}

TEST_CASE("special cases", "[day01]") {
  STATIC_CHECK(part02("L75\nR20") == 1);
  STATIC_CHECK(part02("R75\nL20") == 1);

  STATIC_CHECK(part02("L50\nR50") == 1);
  STATIC_CHECK(part02("L50\nL50") == 1);

  STATIC_CHECK(part02("R50\nR50") == 1);
  STATIC_CHECK(part02("R50\nL50") == 1);

  STATIC_CHECK(part02("L200") == 2);
  STATIC_CHECK(part02("R200") == 2);

  STATIC_CHECK(part02("L150\nL50") == 2);
  STATIC_CHECK(part02("L150\nR50") == 2);

  STATIC_CHECK(part02("R150\nL50") == 2);
  STATIC_CHECK(part02("R150\nR50") == 2);
}
