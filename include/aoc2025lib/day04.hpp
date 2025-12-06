#pragma once

#include <algorithm>
#include <print>
#include <ranges>
#include <string_view>

namespace aoc2025::day04 {

constexpr auto index(const auto width, const auto x, const auto y) {
  return (y * (width + 1)) + x;
}
constexpr auto
in_bounds(const auto width, const auto height, const auto x, const auto y) {
  return x >= 0 and x < width and y >= 0 and y < height;
}
constexpr auto is_roll_of_paper(const auto cell) { return cell == '@'; }
constexpr auto himself(const auto x, const auto y, const auto i, const auto j) {
  return x == i and y == j;
}
constexpr auto neighbours(
    auto input, const auto width, const auto height, const int x, const int y) {
  std::size_t counter = 0;
  for (int i = x - 1; i <= x + 1; i++) {
    for (int j = y - 1; j <= y + 1; j++) {
      if (in_bounds(width, height, i, j) and not himself(x, y, i, j) and
          is_roll_of_paper(input[index(width, i, j)]))
        counter++;
    }
  }
  return counter;
}

struct ParseResult {
  std::string output;
  std::size_t counter;
};

constexpr auto parse_once(std::string_view input) {
  auto output = std::string(input);
  const std::size_t width =
      std::ranges::distance(input.begin(), std::ranges::find(input, '\n'));
  const std::size_t height = input.size() / (width + 1);

  std::size_t counter = 0;
  for (std::size_t i = 0; i < width; i++) {
    for (std::size_t j = 0; j < height; j++) {
      if (not is_roll_of_paper(input[index(width, i, j)]))
        continue;
      if (const auto n = neighbours(
              input, width, height, static_cast<int>(i), static_cast<int>(j));
          n < 4) {
        counter++;
        output[index(width, i, j)] = 'x';
      }
    }
  }

  return ParseResult{output, counter};
}

constexpr auto part01(std::string_view input) -> std::size_t {
  return parse_once(input).counter;
}

constexpr auto part02(std::string_view input) -> std::size_t {
  std::size_t counter = 0;
  auto result = parse_once(input);
  while (result.counter > 0) {
    counter += result.counter;
    result = parse_once(result.output);
  }
  return counter;
}
}; // namespace aoc2025::day04
