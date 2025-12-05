#pragma once

#include <algorithm>
#include <print>
#include <ranges>
#include <string_view>

namespace aoc2025::day02 {

constexpr long to_int(std::string_view sv) {
  long value{};
  auto [ptr, ec] = std::from_chars(sv.data(), sv.data() + sv.size(), value);
  if (ec != std::errc{})
    throw "bad integer";
  return value;
}

constexpr std::string to_string(long num) {
  const size_t buf_size = 10;
  char buf[buf_size]{};
  auto [ptr, ec] = std::to_chars(buf, buf + buf_size, num);
  if (ec != std::errc{})
    throw "bad integer";
  return std::string(buf);
}
// turn a range of chars into a string_view
constexpr auto as_string_view = [](auto &&r) {
  return std::string_view{std::ranges::data(r), std::ranges::size(r)};
};

constexpr auto repeats(std::string_view str, const auto num) {
  std::string output = std::string(str);
  for (std::size_t i = 1; i < num; i++) {
    output += str;
  }
  return output;
}

constexpr auto is_invalid_id_half(std::string_view id) {
  if (id.size() < 2)
    return false;

  const auto half_index = id.size() / 2;
  return id.substr(0, half_index) ==
         id.substr(half_index, std::string_view::npos);
}
constexpr auto is_invalid_id(std::string_view id) {
  if (id.size() < 2)
    return false;

  const auto half_index = id.size() / 2;
  for (std::size_t index = 1; index <= half_index; index++) {
    const auto repeat_number = id.size() / index;
    if (repeats(id.substr(0, index), repeat_number) == id)
      return true;
  }
  return false;
}

constexpr auto part01(std::string_view input) -> long {
  auto data =
      input | std::views::split(',') | std::views::transform([](auto &&rng) {
        auto data = rng | std::views::split('-') |
                    std::views::transform(as_string_view) |
                    std::views::transform(to_int);
        return data;
      });

  auto new_rng = data | std::views::transform([](auto &&rng) {
                   auto begin_it = std::ranges::begin(rng);
                   auto begin = *begin_it;
                   auto end = *std::ranges::next(begin_it);
                   return std::views::iota(begin, end + 1) |
                          std::views::filter([](const auto &num) {
                            auto str = to_string(num);
                            return is_invalid_id_half(str);
                          });
                 }) |
                 std::views::join;
  return std::ranges::fold_left(new_rng, 0, std::plus{});
}
constexpr auto part02(std::string_view input) -> long {
  auto data =
      input | std::views::split(',') | std::views::transform([](auto &&rng) {
        auto data = rng | std::views::split('-') |
                    std::views::transform(as_string_view) |
                    std::views::transform(to_int);
        return data;
      });

  auto new_rng = data | std::views::transform([](auto &&rng) {
                   auto begin_it = std::ranges::begin(rng);
                   auto begin = *begin_it;
                   auto end = *std::ranges::next(begin_it);
                   return std::views::iota(begin, end + 1) |
                          std::views::filter([](const auto &num) {
                            auto str = to_string(num);
                            return is_invalid_id(str);
                          });
                 }) |
                 std::views::join;
  return std::ranges::fold_left(new_rng, 0, std::plus{});
}
}; // namespace aoc2025::day02
