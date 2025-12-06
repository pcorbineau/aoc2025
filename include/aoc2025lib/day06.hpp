#pragma once

#include <algorithm>
#include <charconv>
#include <print>
#include <ranges>
#include <string_view>
#include <vector>

namespace aoc2025::day06 {
enum class Operator { Mul, Plus };
}

template <>
struct std::formatter<aoc2025::day06::Operator> : std::formatter<std::string> {
  auto format(const aoc2025::day06::Operator &op, auto &ctx) const {
    return std::format_to(
        ctx.out(), "{}", op == aoc2025::day06::Operator::Mul ? "*" : "+");
  }
};
namespace aoc2025::day06 {

constexpr auto as_string_view = [](auto &&r) {
  return std::string_view{std::ranges::data(r), std::ranges::size(r)};
};
constexpr auto empty_string(std::string_view str) { return not str.empty(); };
constexpr std::size_t to_int(std::string_view sv) {
  std::size_t value{};
  auto [ptr, ec] = std::from_chars(sv.data(), sv.data() + sv.size(), value);
  if (ec != std::errc{})
    throw "bad integer";
  return value;
}

constexpr auto to_operator(std::string_view str) {
  if (str == "*") {
    return Operator::Mul;
  } else if (str == "+") {
    return Operator::Plus;
  }
  throw;
}

constexpr auto compute(const Operator &op, const auto lhs, const auto rhs) {
  switch (op) {
  case Operator::Mul:
    return lhs * rhs;
  case Operator::Plus:
    return lhs + rhs;
  }
  throw;
}

constexpr auto parse_number_line(std::string_view line) {
  using namespace std::literals;
  return line
         | std::views::split(" "sv)
         | std::views::transform(as_string_view)
         | std::views::filter(empty_string)
         | std::views::transform(to_int)
         | std::ranges::to<std::vector>();
}
constexpr auto parse_operator_line(std::string_view line) {
  using namespace std::literals;
  return line
         | std::views::split(" "sv)
         | std::views::transform(as_string_view)
         | std::views::filter(empty_string)
         | std::views::transform(to_operator)
         | std::ranges::to<std::vector>();
}

constexpr auto part01(std::string_view input) -> std::size_t {
  using namespace std::literals;
  auto lines = input
               | std::views::split('\n')
               | std::views::transform(as_string_view)
               | std::views::filter(empty_string)
               | std::ranges::to<std::vector>();
  auto numbers_list = lines
                      | std::views::reverse
                      | std::views::drop(1)
                      | std::views::transform(parse_number_line);
  auto operators = lines
                   | std::views::reverse
                   | std::views::take(1)
                   | std::views::transform([](std::string_view line) {
                       return parse_operator_line(line);
                     })
                   | std::views::join
                   | std::ranges::to<std::vector>();
  ;
  std::size_t accum = 0;
  for (int y = 0; y < std::ranges::distance(numbers_list[0]); y++) {
    auto tmp = numbers_list[0][y];
    for (int x = 1; x < std::ranges::distance(numbers_list); x++) {
      const auto op = operators[y];
      const auto num = numbers_list[x][y];
      tmp = compute(op, tmp, num);
    }
    accum += tmp;
  }
  return accum;
}

constexpr auto index(const auto width, const auto x, const auto y) {
  return (y * (width + 1)) + x;
}

constexpr auto part02(std::string_view input) -> std::size_t {
  std::size_t output = 0;
  std::vector<std::size_t> nums;
  const int width = static_cast<int>(
      std::ranges::distance(input.begin(), std::ranges::find(input, '\n')));
  const int height = static_cast<int>(input.size() / (width + 1));

  for (int j = width - 1; j >= 0; j--) {
    std::size_t colnum = 0;
    for (int i = 0; i < (height - 1); i++) {
      const auto cell = input[index(width, j, i)];
      if (cell != ' ') {
        colnum = colnum * 10 + (cell - '0');
      }
    }
    if (colnum != 0) {
      nums.push_back(colnum);
    }
    const auto op = input[index(width, j, height - 1)];
    if (op != ' ') {
      switch (op) {
      case '+':
        output += std::ranges::fold_left(nums, 0, std::plus{});
        break;
      case '*':
        output += std::ranges::fold_left(nums, 1, std::multiplies{});
        break;
      default:
        throw;
      }
      nums.clear();
    }
  }
  return output;
}
} // namespace aoc2025::day06
