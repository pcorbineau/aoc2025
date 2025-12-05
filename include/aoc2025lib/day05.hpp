#pragma once

#include <algorithm>
#include <charconv>
#include <print>
#include <ranges>
#include <string_view>
#include <vector>

namespace aoc2025::day05 {

struct Range {
  std::size_t begin;
  std::size_t end;
  constexpr auto operator<=>(const Range &) const = default;

  constexpr auto in_bounds(const auto val) const {
    return val >= begin and val <= end;
  };
};

} // namespace aoc2025::day05

template <>
struct std::formatter<aoc2025::day05::Range> : std::formatter<std::string> {
  auto format(const aoc2025::day05::Range &r, auto &ctx) const {
    // Write directly to the output iterator
    return std::format_to(ctx.out(), "[{}-{}]", r.begin, r.end);
  }
};

namespace aoc2025::day05 {

constexpr auto is_fresh(const Range &range, std::size_t val) {}

template <typename T> constexpr auto as_num(std::string_view input) {
  if (input.empty())
    throw std::runtime_error("empty input");
  T result{};
  auto [ptr, ec] =
      std::from_chars(input.data(), input.data() + input.size(), result);
  if (ec != std::errc{}) {
    throw std::runtime_error("invalid string to num");
  }
  return result;
}

constexpr auto parse_range(std::string_view range) {
  auto separator = std::ranges::find(range, '-');
  if (separator == range.end()) {
    throw std::runtime_error("invalid range format");
  }

  // Create subranges using iterators
  std::string_view first_part(range.begin(), separator);
  std::string_view second_part(separator + 1, range.end());

  return Range{as_num<std::size_t>(first_part),
               as_num<std::size_t>(second_part)};
}

constexpr auto as_string_view(auto &&rng) {
  return std::string_view(&*rng.begin(), std::ranges::distance(rng));
}
constexpr auto to_string_view = [](auto &&rng) {
  return std::string_view(std::ranges::data(rng), std::ranges::size(rng));
};

constexpr auto part01(std::string_view input) -> long {
  using namespace std::literals;
  auto view = input | std::views::split("\n\n"sv);
  auto ranges_it = std::ranges::begin(view);
  auto ranges = as_string_view(*ranges_it) | std::views::split("\n"sv) |
                std::views::transform(to_string_view) |
                std::views::transform(parse_range) |
                std::ranges::to<std::vector>();
  auto values = as_string_view(*std::ranges::next(ranges_it)) |
                std::views::split('\n') |
                std::views::transform(to_string_view) |
                std::views::filter([](auto str) { return not str.empty(); }) |
                std::views::transform([](std::string_view str) {
                  return as_num<std::size_t>(str);
                });

  return std::ranges::distance(
      values | std::views::filter([ranges](const std::size_t val) {
        return std::ranges::any_of(
            ranges, [val](const Range &rng) { return rng.in_bounds(val); });
      }));
}

constexpr auto part02(std::string_view input) -> long {
  using namespace std::literals;
  auto view = input | std::views::split("\n\n"sv);
  auto ranges_it = std::ranges::begin(view);
  auto vec = as_string_view(*ranges_it) | std::views::split("\n"sv) |
             std::views::transform(to_string_view) |
             std::views::transform(parse_range) |
             std::ranges::to<std::vector>();
  std::ranges::sort(vec, {}, &Range::begin);
  std::vector<Range> output{vec[0]};
  output.reserve(vec.size());
  for (const auto &rng : vec) {
    auto &last = output.back();
    if (rng.begin > last.end) {
      output.push_back(rng);
      continue;
    }

    if (rng.end > last.end) {
      last.end = rng.end;
      continue;
    }
  }
  return std::ranges::fold_left(
      output, 0uz, [](const auto accum, const auto &rng) {
        return accum + rng.end - rng.begin + 1;
      });
}
} // namespace aoc2025::day05
