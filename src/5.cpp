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

using namespace std;
using namespace fmt;

int main(int argc, char *argv[]) {
  assert(argc == 2);

  auto in = process_input(argv[1]);

  int max = 0;
  vector<int> seats;

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
    seats.emplace_back(seat_id);
    if (seat_id > max) {
      max = seat_id;
    }
  }
  print("Part 1: {}\n", max);
  ranges::sort(seats);
  for (int i = 1; i < seats.size(); i++) {
    if ((seats[i] - seats[i - 1]) == 2) {
      print("Part 2: {}\n", seats[i] - 1);
      break;
    }
  }

  return 0;
}