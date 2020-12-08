#include <fmt/core.h>
#include <fmt/ranges.h>

#include <cassert>
#include <numeric>
#include <string>
#include <vector>

#include "aoc_util.h"

using namespace std;
using namespace fmt;

int main(int argc, char *argv[]) {
  assert(argc == 2);

  const auto in = process_input(argv[1]);

  constexpr array keys = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};

  bool nl = true;
  int counter = 0;
  int found = 0;
  for (const auto &line : in) {
    if (line.empty()) {
      nl = true;
      continue;
    }
    if (nl) {
      nl = false;
      if (counter == keys.size()) {
        // found them all!
        found++;
      }
      counter = 0;
    }
    for (const auto &key : keys) {
      if (line.find(key) != string::npos) {
        counter++;
      }
    }
  }

  // could be one more after the loop
  if (counter == keys.size()) {
    found++;
  }

  print("Part 1: {}\n", found);

  return 0;
}
