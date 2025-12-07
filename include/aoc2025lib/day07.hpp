#pragma once

#include <algorithm>
#include <charconv>
#include <print>
#include <ranges>
#include <string_view>
#include <vector>

namespace aoc2025::day07 {

constexpr std::size_t index(const auto width, const auto x, const auto y) {
  return ((width + 1) * y) + x;
}
constexpr int width(std::string_view input) {
  return static_cast<int>(std::ranges::distance(
      std::ranges::begin(input), std::ranges::find(input, '\n')));
}
constexpr int height(std::string_view input) {
  return static_cast<int>(input.size() / (width(input) + 1));
}

constexpr auto in_bounds(const auto input, const auto x, const auto y) {
  return x >= 0 and x < width(input) and y >= 0 and y < height(input);
}

constexpr auto parse(std::string &input, const auto x, const auto y) {
  if (not in_bounds(input, x, y)) {
    return 0;
  }
  const auto cell = input[index(width(input), x, y)];
  switch (cell) {
  case '.':
    input[index(width(input), x, y)] = '|';
    return parse(input, x, y + 1);
  case '^':
    return parse(input, x - 1, y) + parse(input, x + 1, y) + 1;
  case '|':
    return 0;
  default:
    throw;
  }
}

constexpr auto part01(std::string_view input) -> std::size_t {
  // find S first line
  auto s_index = std::ranges::distance(std::ranges::begin(input),
                                       std::ranges::find(input, 'S'));
  std::string str_input{input};
  return parse(str_input, s_index, 1);
}

constexpr auto parse2(std::string_view input,
                      const auto x,
                      const auto y,
                      std::vector<long long> &timelines) {
  if (not in_bounds(input, x, y)) {
    return 0LL;
  }
  if (y == (height(input) - 1)) {
    return 1LL;
  }
  auto &cache = timelines[index(width(input), x, y)];
  if (cache != -1) {
    return cache;
  }
  const auto cell = input[index(width(input), x, y)];
  if (cell == '.') {
    cache = parse2(input, x, y + 1, timelines);
  } else if (cell == '^') {
    cache = parse2(input, x - 1, y, timelines)
            + parse2(input, x + 1, y, timelines);
  } else {
    throw;
  }

  return cache;
}
constexpr auto part02(std::string_view input) -> std::size_t {
  auto s_index = std::ranges::distance(std::ranges::begin(input),
                                       std::ranges::find(input, 'S'));
  std::vector<long long> timelines(input.size(), -1LL);
  return static_cast<std::size_t>(parse2(input, s_index, 1, timelines));
}
} // namespace aoc2025::day07
