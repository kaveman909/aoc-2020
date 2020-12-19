#include <fmt/core.h>
#include <fmt/ranges.h>

#include <algorithm>
#include <cassert>
#include <iostream>
#include <itertools.hpp>
#include <numeric>
#include <string>
#include <vector>

#include "aoc_util.h"

using namespace std;
using namespace fmt;

int main(int argc, char *argv[]) {
  assert(argc == 2);

  auto seating =
      process_input(argv[1], [](const string &s) { return s.size(); });

  print("{}\n", seating);

  return 0;
}
