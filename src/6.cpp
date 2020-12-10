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

  string all_answers;
  vector<int> totals;
  for (const auto &line : in) {
    if (line.empty()) {
      ranges::sort(all_answers);
      auto [f, l] = ranges::unique(all_answers);
      all_answers.erase(f, l);
      totals.emplace_back(all_answers.size());
      all_answers = "";
    } else {
      all_answers += line;
    }
  }

  print("Part 1: {}\n", accumulate(totals.begin(), totals.end(), 0));

  return 0;
}
