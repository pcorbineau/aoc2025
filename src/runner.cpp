#include <aoc2025lib/day01.hpp>
#include <aoc2025lib/day02.hpp>
#include <filesystem>
#include <fstream>
#include <string>

std::string read_file(const std::filesystem::path &filename) {
  std::ifstream inputFileStream(filename);
  // Construct string directly from stream iterators
  std::string fileContent((std::istreambuf_iterator<char>(inputFileStream)),
                          std::istreambuf_iterator<char>());
  return fileContent;
}

constexpr std::array part01 = {
    aoc2025::day01::part01,
    aoc2025::day02::part01,
};

constexpr std::array part02 = {
    aoc2025::day01::part02,
    aoc2025::day02::part02,
};
void print_result(const int day_number, std::string_view input) {
  std::println("day {:02}", day_number);
  std::println("part01 : {}", part01[day_number - 1](input));
  std::println("part02 : {}", part02[day_number - 1](input));
}

int main(int argc, const char *argv[]) {
  const auto day_number = argv[1];
  const auto input_file = argv[2];
  const auto file_content = read_file(input_file);
  print_result(std::stoi(day_number), file_content);
}
