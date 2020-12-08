#include <fmt/core.h>
#include <fmt/ranges.h>
#include "aoc_util.h"
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace fmt;

int main(int argc, char *argv[]) {
  assert(argc == 2);

  auto in = process_input(argv[1]);
  print("{}\n", in);

  return 0;
}
