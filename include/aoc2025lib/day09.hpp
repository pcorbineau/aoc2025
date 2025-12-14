#pragma once

#include <algorithm>
#include <charconv>
#include <cmath>
#include <print>
#include <ranges>
#include <string_view>
#include <vector>

namespace aoc2025::day09 {
struct Position {
  std::size_t x;
  std::size_t y;
};
} // namespace aoc2025::day09
template <>
struct std::formatter<aoc2025::day09::Position> : std::formatter<std::string> {
  auto format(const aoc2025::day09::Position &pos, auto &ctx) const {
    // Write directly to the output iterator
    return std::format_to(ctx.out(), "[{}-{}]", pos.x, pos.y);
  }
};

namespace aoc2025::day09 {
constexpr std::size_t to_int(std::string_view sv) {
  std::size_t value{};
  auto [ptr, ec] = std::from_chars(sv.data(), sv.data() + sv.size(), value);
  if (ec != std::errc{})
    throw "bad integer";
  return value;
}
constexpr auto as_string_view = [](auto &&rng) {
  return std::string_view(&*rng.begin(), std::ranges::distance(rng));
};

constexpr auto empty_string(std::string_view str) { return not str.empty(); };

constexpr auto parse_line(std::string_view line) {
  auto separator = line.find(',');
  return Position{
      .x = to_int(line.substr(0, separator)),
      .y = to_int(line.substr(separator + 1, std::string_view::npos)),
  };
}

constexpr auto pairwise_combinations(auto &&range) {
  return std::views::transform(
             std::views::enumerate(range),
             [&](auto indexed) {
               auto [i, x] = indexed;
               return std::views::transform(
                   std::views::drop(range, i + 1),
                   [=](auto const &y) { return std::make_pair(x, y); });
             })
         | std::views::join;
}

constexpr auto area(const Position &lhs, const Position &rhs) {
  const auto width
      = std::abs(static_cast<int64_t>(rhs.x) - static_cast<int64_t>(lhs.x)) + 1;
  const auto height
      = std::abs(static_cast<int64_t>(rhs.y) - static_cast<int64_t>(lhs.y)) + 1;
  return static_cast<std::size_t>(width * height);
}

constexpr auto part01(std::string_view input) -> std::size_t {
  using namespace std::literals;
  auto view = input
              | std::views::split("\n"sv)
              | std::views::transform(as_string_view)
              | std::views::filter(empty_string)
              | std::views::transform(parse_line);
  return std::ranges::max(pairwise_combinations(view)
                          | std::views::transform([](const auto &pair) {
                              return area(pair.first, pair.second);
                            }));
}

constexpr auto part02(std::string_view input) -> std::size_t {
  return input.size();
}
} // namespace aoc2025::day09
