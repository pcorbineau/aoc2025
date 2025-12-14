#pragma once

#include <algorithm>
#include <charconv>
#include <cmath>
#include <print>
#include <ranges>
#include <string_view>
#include <vector>

namespace aoc2025::day10 {
constexpr auto part01(std::string_view input) -> std::size_t {
  using namespace std::literals;
  return input.size();
}

constexpr auto part02(std::string_view input) -> std::size_t {
  return input.size();
}
} // namespace aoc2025::day10
