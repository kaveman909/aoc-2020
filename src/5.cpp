#include <fmt/core.h>
#include <fmt/ranges.h>

#include <algorithm>
#include <array>
#include <cassert>
#include <numeric>
#include <regex>
#include <string>
#include <vector>

#include "aoc_util.h"

int main(int argc, char *argv[]) {
  assert(argc == 2);

  auto in = process_input(argv[1]);

  int max = 0;

  for (auto &line : in) {
    for (auto &c : line) {
      switch (c) {
        case 'F':
        case 'L':
          c = '0';
          break;
        case 'B':
        case 'R':
          c = '1';
          break;
      }
    }
    const auto row = stoi(line.substr(0, 7), 0, 2);
    const auto column = stoi(line.substr(7), 0, 2);
    const auto seat_id = row * 8 + column;
    if (seat_id > max) {
      max = seat_id;
    }
  }

  fmt::print("Part 1: {}\n", max);

  return 0;
}