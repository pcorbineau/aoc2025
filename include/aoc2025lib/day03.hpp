#pragma once

#include <algorithm>
#include <print>
#include <ranges>
#include <string_view>

namespace aoc2025::day03 {

constexpr auto as_num(char c) { return c - '0'; }
struct lines_t : std::ranges::range_adaptor_closure<lines_t> {
  // operator() for pipe syntax:
  template <std::ranges::viewable_range R> auto operator()(R &&r) const {
    // split on '\n', then transform subranges into string_view
    return std::forward<R>(r) | std::views::split('\n') |
           std::views::transform([](auto &&subrange) {
             // subrange is a range of characters
             return std::string_view{std::ranges::data(subrange),
                                     std::ranges::size(subrange)};
           });
  }
};

inline constexpr lines_t lines{};

constexpr auto largest_joltage(const std::size_t window, std::string_view input)
    -> std::size_t {
  std::size_t max = 0;
  std::size_t start = 0;
  for (std::size_t i = 0; i < window; i++) {
    std::size_t value = 0;
    const auto end = input.size() - window + 1 + i;
    for (std::size_t j = start; j < end; j++) {
      const auto c = static_cast<std::size_t>(as_num(input[j]));
      if (c > value) {
        value = c;
        start = j + 1;
      }
    }
    max = (max * 10) + value;
  }
  return max;
}
constexpr auto empty_line = [](auto &&rng) { return rng.size() != 0; };

constexpr auto part01(std::string_view input) -> std::size_t {
  return std::ranges::fold_left(
      input | lines | std::views::filter(empty_line) |
          std::views::transform(
              [](std::string_view line) { return largest_joltage(2, line); }),
      0,
      std::plus{});
}

constexpr auto part02(std::string_view input) -> std::size_t {
  return std::ranges::fold_left(
      input | lines | std::views::filter(empty_line) |
          std::views::transform(
              [](std::string_view line) { return largest_joltage(12, line); }),
      0,
      std::plus{});
}
}; // namespace aoc2025::day03
