cmake_minimum_required(VERSION 3.27)

project(aoc2025)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
file(
	CREATE_LINK
	${CMAKE_BINARY_DIR}/compile_commands.json
	${CMAKE_SOURCE_DIR}/compile_commands.json
	SYMBOLIC
)


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
# aoc2025 library
add_library(aoc2025lib INTERFACE)
target_sources(
	aoc2025lib
	INTERFACE
	${CMAKE_SOURCE_DIR}/include/aoc2025lib/day01.hpp
	${CMAKE_SOURCE_DIR}/include/aoc2025lib/day02.hpp
)
target_include_directories(
	aoc2025lib
	INTERFACE
	${CMAKE_SOURCE_DIR}/include
)
target_compile_features(aoc2025lib INTERFACE cxx_std_23)
# -----------------------------------------------------------------------------
# aoc2025 executable

add_executable(
	aoc2025 src/runner.cpp
)
target_link_libraries(aoc2025 PRIVATE aoc2025lib)
# -----------------------------------------------------------------------------
# aoc2025 test executable

add_executable(
	aoc2025test
	tests/day01.cpp
	tests/day02.cpp
)
target_link_libraries(aoc2025test PRIVATE aoc2025lib Catch2::Catch2WithMain)
# -----------------------------------------------------------------------------
# custom target run to run test
add_custom_target(
	run
	COMMAND $<TARGET_FILE:aoc2025test> --order rand
	COMMENT "Running aoc2025 tests"
	DEPENDS aoc2025
	USES_TERMINAL
)
