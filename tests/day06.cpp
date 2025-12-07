#include <aoc2025lib/day06.hpp>
#include <catch2/catch_test_macros.hpp>

namespace input {
static constexpr auto test =
    R"(123 328  51 64 
 45 64  387 23 
  6 98  215 314
*   +   *   +  
)";
}

using namespace aoc2025::day06;

TEST_CASE("parts", "[day06]") {
  STATIC_CHECK(part01(input::test) == 4277556);
  STATIC_CHECK(part02(input::test) == 3263827);
}

TEST_CASE("parse_number_line", "[day06]") {
  STATIC_CHECK(parse_number_line("123 328  51 64")
               == std::vector<std::size_t>{123, 328, 51, 64});
  STATIC_CHECK(parse_number_line(" 45 64  387 23 ")
               == std::vector<std::size_t>{45, 64, 387, 23});
}

TEST_CASE("parse_operator_line", "[day06]") {
  STATIC_CHECK(
      parse_operator_line("*   +   *   +")
      == std::vector<Operator>{
          Operator::Mul, Operator::Plus, Operator::Mul, Operator::Plus});
}
