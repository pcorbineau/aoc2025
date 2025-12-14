#pragma once

#include <algorithm>
#include <charconv>
#include <cmath>
#include <print>
#include <ranges>
#include <string_view>
#include <vector>

namespace aoc2025::day08 {

struct Position {
  std::size_t x;
  std::size_t y;
  std::size_t z;
  constexpr auto operator<=>(const Position &) const = default;
};
struct Pair {
  Position lhs;
  Position rhs;
  std::size_t distance;
  constexpr Pair(const auto lhs, const auto rhs)
      : lhs(lhs), rhs(rhs), distance(root_distance(lhs, rhs)) {}

  friend constexpr auto operator==(const Pair &lhs, const Pair &rhs) {
    return lhs.lhs == rhs.lhs and lhs.rhs == rhs.rhs;
  }
};

} // namespace aoc2025::day08

template <>
struct std::formatter<aoc2025::day08::Position> : std::formatter<std::string> {
  auto format(const aoc2025::day08::Position &pos, auto &ctx) const {
    // Write directly to the output iterator
    return std::format_to(ctx.out(), "[{}-{}-{}]", pos.x, pos.y, pos.z);
  }
};
template <>
struct std::formatter<aoc2025::day08::Pair> : std::formatter<std::string> {
  auto format(const aoc2025::day08::Pair &posdis, auto &ctx) const {
    // Write directly to the output iterator
    return std::format_to(
        ctx.out(), "{} <-> {} : {}\n", posdis.lhs, posdis.rhs, posdis.distance);
  }
};

namespace aoc2025::day08 {

constexpr auto root_distance(const Position &lhs, const Position &rhs) {
  const std::size_t x = rhs.x - lhs.x;
  const std::size_t y = rhs.y - lhs.y;
  const std::size_t z = rhs.z - lhs.z;
  const auto res = (x * x) + (y * y) + (z * z);
  std::println("{} {} => {}", lhs, rhs, res);
  return res;
}

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

constexpr auto parse_line(std::string_view line) -> Position {
  using namespace std::literals;
  auto rng = line
             | std::views::split(","sv)
             | std::views::transform(as_string_view)
             | std::views::transform(to_int);
  auto x = std::ranges::begin(rng);
  auto y = std::ranges::next(x);
  auto z = std::ranges::next(y);
  return Position{*x, *y, *z};
}

// constexpr auto cartesian_product_pairs(auto &&rng) {
//   const std::size_t size = std::ranges::distance(rng);
//   return std::views::iota(0uz, size)
//          | std::views::transform([&rng, size](std::size_t i) {
//              return std::views::iota(i + 1, size)
//                     | std::views::transform([i, &rng](std::size_t j) {
//                         return Pair(root_distance(rng[i], rng[j]));
//                       });
//            });
// }

constexpr auto part01(std::string_view input) -> std::size_t {
  using namespace std::literals;
  // auto positions = input
  //                  | std::views::split("\n"sv)
  //                  | std::views::transform(as_string_view)
  //                  | std::views::filter(empty_string)
  //                  | std::views::transform(parse_line);
  // auto pairs = cartesian_product_pairs(positions);
  // std::ranges::sort(pairs, {}, &Pair::lhs);
  // std::println("BEFORE\n{}", pairs | std::views::take(10));
  // const auto [first, last]
  //     = std::ranges::unique(pairs,
  //                           [](const auto &lhs, const auto &rhs) {
  //                             return lhs.lhs == rhs.lhs and lhs.rhs ==
  //                             rhs.rhs;
  //                           },
  //                           {});
  // pairs.erase(first, last);
  // std::println("AFTER\n{}", pairs | std::views::take(10));
  //
  // std::ranges::sort(pairs, {}, &Pair::distance);
  // auto closest_pairs = pairs | std::views::take(10);
  // std::println("################");
  // std::println("{}", closest_pairs);
  return input.size();
}

constexpr auto part02(std::string_view input) -> std::size_t {
  return input.size();
}
} // namespace aoc2025::day08
