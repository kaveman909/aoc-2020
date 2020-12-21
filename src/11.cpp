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

enum class Seat { FLOOR, EMPTY, OCCUPIED };

template <>
struct fmt::formatter<Seat> : formatter<string_view> {
  // parse is inherited from formatter<string_view>.
  template <typename FormatContext>
  auto format(Seat c, FormatContext &ctx) {
    string_view name = "unknown";
    switch (c) {
      case Seat::FLOOR:
        name = ".";
        break;
      case Seat::EMPTY:
        name = "L";
        break;
      case Seat::OCCUPIED:
        name = "#";
        break;
    }
    return formatter<string_view>::format(name, ctx);
  }
};

auto get_neighbors(const vector<vector<Seat>> &seating, const int x,
                   const int y) {
  vector<Seat> neighbors;
  const int x_min = (x == 0) ? x : x - 1;
  const int x_max = (x == (seating[0].size() - 1)) ? x : x + 1;
  const int y_min = (y == 0) ? y : y - 1;
  const int y_max = (y == (seating.size() - 1)) ? y : y + 1;

  for (int xi = x_min; xi <= x_max; xi++) {
    for (int yi = y_min; yi <= y_max; yi++) {
      if (((x != xi) || (y != yi)) && (seating[yi][xi] != Seat::FLOOR)) {
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
  auto seating_copy = seating;
  auto loop_counter = 0;
  while (1) {
    loop_counter++;
    for (int y = 0; y < y_max; y++) {
      for (int x = 0; x < x_max; x++) {
        auto &current_seat = seating_copy[y][x];
        if (current_seat == Seat::FLOOR) {
          continue;
        }
        const auto neighbors = get_neighbors(seating, x, y);
        if (current_seat == Seat::EMPTY) {
          // If a seat is empty (L) and there are no occupied seats adjacent to
          // it, the seat becomes occupied
          if (ranges::none_of(neighbors, [](Seat seat) {
                return seat == Seat::OCCUPIED;
              })) {
            current_seat = Seat::OCCUPIED;
          }  // no else
        } else if (current_seat == Seat::OCCUPIED) {
          // If a seat is occupied (#) and four or more seats adjacent to it are
          // also occupied, the seat becomes empty.
          if (ranges::count(neighbors, Seat::OCCUPIED) >= 4) {
            current_seat = Seat::EMPTY;
          }  // no else
        }    // Otherwise, the seat's state does not change.
      }
    }
    if (seating != seating_copy) {
      seating = seating_copy;
    } else {
      int sum = 0;
      for (const auto &row : seating) {
        // print("{}\n", join(row, ""));
        sum =
            transform_reduce(row.begin(), row.end(), sum, plus(),
                             [](Seat seat) { return seat == Seat::OCCUPIED; });
      }
      print("Part 1: {}\n", sum);
      return 0;
    }
  }
}
