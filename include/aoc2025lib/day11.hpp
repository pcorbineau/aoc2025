#pragma once

#include <algorithm>
#include <charconv>
#include <cmath>
#include <ranges>
#include <string_view>
#include <vector>

namespace aoc2025::day11 {
constexpr auto as_string_view = [](auto &&rng) {
  return std::string_view(&*rng.begin(), std::ranges::distance(rng));
};
constexpr auto empty_string(std::string_view str) { return not str.empty(); };

template <typename K, typename V, std::size_t N> struct constexpr_map {
  std::array<std::pair<K, V>, N> data{};
  std::size_t sz{0}; // actual used size

  constexpr constexpr_map() = default;

  // Construct from array + size
  constexpr constexpr_map(std::array<std::pair<K, V>, N> arr, std::size_t s)
      : data(arr), sz(s) {
    // Sort only the first sz elements
    std::ranges::sort(
        data.begin(), data.begin() + sz, {}, &std::pair<K, V>::first);
  }

  constexpr const V &at(const K &key) const {
    auto it = std::ranges::lower_bound(
        data.begin(), data.begin() + sz, key, {}, &std::pair<K, V>::first);
    if (it == data.begin() + sz || it->first != key) {
      throw std::out_of_range("key not found");
    }
    return it->second;
  }
  constexpr auto in_bounds(const auto &it, const auto &key) const {
    return not(it == data.begin() + sz || it->first != key);
  }
  constexpr auto find(const K &key) const {
    return std::ranges::lower_bound(
        data.begin(), data.begin() + sz, key, {}, &std::pair<K, V>::first);
  }

  constexpr const V &operator[](const K &key) const { return at(key); }

  constexpr std::size_t size() const { return sz; }
};

constexpr auto parse_line(std::string_view line) {
  auto double_colon_it = line.find(':');
  return std::make_pair(line.substr(0, double_colon_it),
                        line.substr(double_colon_it + 2, std::string_view::npos)
                            | std::views::split(' ')
                            | std::views::transform(as_string_view)
                            | std::ranges::to<std::vector>());
}

template <typename R, typename K, typename V, std::size_t MAX_LINES>
constexpr auto to_constexpr_map(R &&r) {
  std::array<std::pair<K, V>, MAX_LINES> arr{};
  std::size_t sz = 0;

  for (auto &&item : r) {
    if (sz >= MAX_LINES)
      throw std::out_of_range("range exceeds MAX_LINES");
    arr[sz++] = item;
  }

  return constexpr_map<K, V, MAX_LINES>{arr, sz};
}
static constexpr auto MY_MAX_LINES = 1024;

constexpr auto try_get(const auto &vec, const auto &key)
    -> std::optional<std::size_t> {
  auto it = std::ranges::find_if(
      vec, [key](const auto &p) { return p.first == key; });
  if (it == std::ranges::end(vec))
    return std::nullopt;
  return it->second;
}
constexpr auto modify_or_emplace(auto &vec, const auto &key, const auto &val) {
  auto it = std::ranges::find_if(
      vec, [key](const auto &p) { return p.first == key; });
  if (it == std::ranges::end(vec)) {
    vec.emplace_back(key, val);
  } else {
    it->second = val;
  }
}

constexpr auto
solve1(const auto &connections, std::string_view from, std::string_view to) {
  auto cache = std::vector<std::pair<std::string_view, std::size_t>>{};
  auto dfs = [&](this auto self, std::string_view current) -> std::size_t {
    if (current == to) {
      return 1;
    }
    if (auto cached = try_get(cache, current)) {
      return *cached;
    }
    auto it = connections.find(current);
    if (not connections.in_bounds(it, current)) {
      return 0;
    }
    const auto count = std::ranges::fold_left(
        it->second | std::views::transform(self), 0, std::plus{});
    modify_or_emplace(cache, current, count);
    return count;
  };
  return dfs(from);
}

constexpr auto part01(std::string_view input) -> std::size_t {
  using namespace std::literals;
  auto res = input
             | std::views::split("\n"sv)
             | std::views::transform(as_string_view)
             | std::views::filter(empty_string)
             | std::views::transform(parse_line);
  auto devices = to_constexpr_map<decltype(res),
                                  std::string_view,
                                  std::vector<std::string_view>,
                                  MY_MAX_LINES>(std::move(res));
  return solve1(devices, "you"sv, "out"sv);
}

constexpr auto
solve2(const auto &connections,
       std::string_view from,
       std::string_view to,
       const std::pair<std::string_view, std::string_view> &must_visit) {
  return (solve1(connections, from, must_visit.first)
          * solve1(connections, must_visit.first, must_visit.second)
          * solve1(connections, must_visit.second, to))
         + (solve1(connections, from, must_visit.second)
            * solve1(connections, must_visit.second, must_visit.first)
            * solve1(connections, from, to));
}

constexpr auto part02(std::string_view input) -> std::size_t {
  using namespace std::literals;
  auto res = input
             | std::views::split("\n"sv)
             | std::views::transform(as_string_view)
             | std::views::filter(empty_string)
             | std::views::transform(parse_line);
  auto devices = to_constexpr_map<decltype(res),
                                  std::string_view,
                                  std::vector<std::string_view>,
                                  MY_MAX_LINES>(std::move(res));
  return solve2(devices, "svr"sv, "out"sv, {"fft"sv, "dac"sv});
}
} // namespace aoc2025::day11
