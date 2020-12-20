#include <fmt/core.h>
#include <fmt/ranges.h>

#include <algorithm>
#include <cassert>
#include <iostream>
#include <itertools.hpp>
#include <map>
#include <numeric>
#include <string>
#include <vector>

#include "aoc_util.h"

using namespace std;
using namespace fmt;

enum class Seat { FLOOR, EMPTY, TAKEN };

auto get_neighbors(const vector<vector<Seat>> seating, const int x,
                   const int y) {
  vector<Seat> neighbors;
  const int x_min = (x == 0) ? x : x - 1;
  const int x_max = (x == (seating[0].size() - 1)) ? x : x + 1;
  const int y_min = (y == 0) ? y : y - 1;
  const int y_max = (y == (seating.size() - 1)) ? y : y + 1;

  for (int xi = x_min; xi < x_max; xi++) {
    for (int yi = y_min; yi < y_max; yi++) {
      if ((x != xi) && (y != yi) && (seating[yi][xi] != Seat::FLOOR)) {
        neighbors.emplace_back(seating[yi][xi]);
      }
    }
  }

  return neighbors;
}

int main(int argc, char *argv[]) {
  assert(argc == 2);

  auto seating = process_input(argv[1], [](const string &s) {
    vector<Seat> v;
    map<char, Seat> m = {{'.', Seat::FLOOR}, {'L', Seat::EMPTY}};
    transform(s.begin(), s.end(), back_inserter(v),
              [&m](char c) { return m[c]; });
    return v;
  });

  const int x_max = seating[0].size();
  const int y_max = seating.size();

  for (int x = 0; x < x_max; x++) {
    for (int y = 0; y < y_max; y++) {
      const auto neighbors = get_neighbors(seating, x, y);
    }
  }

  return 0;
}
