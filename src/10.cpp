#include <fmt/core.h>
#include <fmt/ranges.h>

#include <algorithm>
#include <cassert>
#include <itertools.hpp>
#include <numeric>
#include <string>
#include <vector>

#include "aoc_util.h"

using namespace std;
using namespace fmt;

int main(int argc, char *argv[]) {
  assert(argc == 2);

  auto joltages = process_input(
      argv[1], +[](const string &x) { return stoi(x); });

  ranges::sort(joltages);
  joltages.insert(joltages.begin(), 0);
  vector joltages2(joltages.begin() + 1, joltages.end());
  joltages2.emplace_back(joltages2.back() + 3);
  auto joltage_pairs = iter::zip(joltages, joltages2);

  int one = 0;
  vector<int> one_range;
  for (const auto &[lo, hi] : joltage_pairs) {
    if ((hi - lo) == 1) {
      one++;
    } else {
      one_range.emplace_back(one);
      one = 0;
    }
  }

  print("Part 1: {}\n",
        accumulate(one_range.begin(), one_range.end(), 0) * one_range.size());

  array lookup{1, 1, 2, 4, 7, 13, 24};
  print("Part 2: {}\n",
        transform_reduce(one_range.begin(), one_range.end(), 1ul, multiplies(),
                         [&lookup](int x) { return lookup[x]; }));

  return 0;
}
