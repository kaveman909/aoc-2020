#include <fmt/core.h>
#include <fmt/ranges.h>

#include <algorithm>
#include <cassert>
#include <numeric>
#include <string>
#include <vector>

#include "aoc_util.h"

using namespace std;
using namespace fmt;

int main(int argc, char *argv[]) {
  assert(argc == 2);
  const int PRE_LEN = 25;
  const auto xmas = process_input(
      argv[1], +[](const string &x) { return stoul(x); });

  size_t st = 0;
  bool found = true;
  unsigned long weakness = 0;
  while (st < xmas.size() - PRE_LEN) {
    if(!found) {
      weakness = xmas[st + PRE_LEN - 1];
      print("Part 1: {}\n", weakness);
      break;
    }
    found = false;
    for (size_t i = st; i < PRE_LEN + st; i++) {
      if (found) {
        break;
      }
      for (size_t j = i + 1; j < PRE_LEN + st; j++) {
        const auto sum = xmas[i] + xmas[j];
        if (sum == xmas[st + PRE_LEN]) {
          found = true;
          break;
        }
      }
    }
    st++;
  }

  // Begin Part 2
  auto start_it = xmas.begin();
  auto end_it = start_it + 1;
  unsigned long sum = 0;
  while(1) {
    if ((end_it == xmas.end()) || (sum > weakness)) {
      start_it++;
      end_it = start_it + 1;
    }
    sum = accumulate(start_it, end_it, 0UL);
    if (sum == weakness) {
      const auto &max = *max_element(start_it, end_it);
      const auto &min = *min_element(start_it, end_it);
      print("Part 2: {}\n", min + max);
      return 0;
    }
    end_it++;
  }
  return 1;
}
