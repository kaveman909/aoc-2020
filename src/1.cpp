#include <fmt/color.h>
#include <fmt/core.h>

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "aoc_util.h"

using namespace std;
using namespace fmt;

int main(int argc, char *argv[]) {
  assert(argc == 2);

  const int TARGET = 2020;

  auto v = process_input(
      argv[1], +[](const string &x) { return stoi(x); });

  // Since there's lots of large numbers that won't add to 2020, will be faster
  // in the long run if we sort the list first (I would think... though could be
  // wrong!)
  sort(v.begin(), v.end());
  bool found = false;

  for (const auto &i : v) {
    for (const auto &j : v) {
      for (const auto &k : v) {
        if (!found && ((j + k) == TARGET)) {
          print(emphasis::bold | fg(color::forest_green), "Part 1: {}\n",
                j * k);
          found = true;
        } else if ((i + j + k) == TARGET) {
          print(emphasis::bold | fg(color::forest_green), "Part 2: {}\n",
                i * j * k);
          return 0;
        }
      }
    }
  }

  return 1;
}
