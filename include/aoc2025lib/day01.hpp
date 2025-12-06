#pragma once

#include <algorithm>
#include <cassert>
#include <charconv>
#include <cstdint>
#include <iterator>
#include <print>
#include <ranges>
#include <stdexcept>
#include <string_view>

namespace aoc2025::day01 {
struct Rotation {
  enum class Direction { Left = -1, Right = +1 } dir;
  int val;
};
constexpr auto parse(char c) -> Rotation::Direction {
  switch (c) {
  case 'L':
    return Rotation::Direction::Left;
  case 'R':
    return Rotation::Direction::Right;
  }
  throw std::runtime_error("invalid Rotation::Direction char (either L or R )");
}
constexpr auto parse(auto str) -> Rotation {
  const auto dir = parse(str[0]);
  int result{};
  const auto [ptr, ec]
      = std::from_chars(str.data() + 1, str.data() + str.size(), result);

  if (ec != std::errc{})
    throw std::runtime_error("invalid int from rotation");

  return {
      .dir = dir,
      .val = result,
  };
}

constexpr auto compute(const Rotation &rot, int last) {
  const int val = last + static_cast<int>(rot.dir) * rot.val;
  return (val % 100 + 100) % 100;
}

struct ComputeResult {
  int value;   // new dial value
  int passes0; // number of times dial passed 0 in this rotation

  constexpr auto operator<=>(const ComputeResult &) const = default;
};

constexpr ComputeResult rotate(const Rotation &rot, int last) {
  const int raw = last + int(rot.dir) * rot.val;
  const int result = (raw % 100 + 100) % 100;
  const int passes0 = [raw, last] {
    if (last != 0 and raw <= 0)
      return (std::abs(raw) / 100) + 1;
    else
      return std::abs(raw) / 100;
  }();

  return {.value = result, .passes0 = passes0};
}

constexpr auto part01(std::string_view input) -> std::size_t {
  using namespace std::literals;

  auto dial_transform = [last = 50](auto compute) mutable {
    return std::views::transform([=](const auto &rotation) mutable {
      last = compute(rotation, last);
      return last;
    });
  };

  return std::ranges::count(
      input
          | std::ranges::views::split("\n"sv)
          | std::views::filter([](auto rng) { return not rng.empty(); })
          | std::views::transform([](auto rng) {
              return parse(std::string_view{rng.data(), rng.size()});
            })
          | dial_transform(compute),
      0);
}
constexpr auto part02(std::string_view input) -> std::size_t {
  using namespace std::literals;

  auto dial_transform = [last = 50](auto compute) {
    return std::views::transform([=](const auto &rotation) mutable {
      auto result = compute(rotation, last);
      last = result.value;
      return result.passes0;
    });
  };

  auto rotations = input
                   | std::ranges::views::split("\n"sv)
                   | std::views::filter([](auto rng) { return !rng.empty(); })
                   | std::views::transform([](auto rng) {
                       return parse(std::string_view{rng.data(), rng.size()});
                     });

  // Example: count zeros
  return std::ranges::fold_left(
      rotations | dial_transform(rotate), 0, std::plus{});
}
}; // namespace aoc2025::day01
