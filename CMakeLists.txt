cmake_minimum_required(VERSION 3.27)

project(aoc2025)

# -----------------------------------------------------------------------------
# CATCH2
Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.8.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)
# -----------------------------------------------------------------------------

add_library(aoc2025lib INTERFACE)
target_sources(
	aoc2025lib
	INTERFACE
	${CMAKE_SOURCE_DIR}/include/aoc2025lib/day01.hpp
)
target_compile_features(aoc2025lib INTERFACE cxx_std_23)

add_executable(
	aoc2025
	tests/day01.cpp
)
target_link_libraries(aoc2025 PRIVATE aoc2025lib Catch2::Catch2WithMain)
