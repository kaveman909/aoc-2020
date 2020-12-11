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
  vector<int> totals2;
  vector<string> group;
  for (const auto &line : in) {
    if (line.empty()) {
      // Part 1 code
      ranges::sort(all_answers);
      auto [f, l] = ranges::unique(all_answers);
      all_answers.erase(f, l);
      totals.emplace_back(all_answers.size());
      all_answers = "";

      // Part 2 code
      map<char, int> m;
      int counter = 0;
      for (const auto &member : group) {
        for (const auto &answer : member) {
          if (m.contains(answer)) {
            m[answer]++;
          } else {
            m[answer] = 1;
          }
        }
      }
      for (const auto &[key, value] : m) {
        if (value == group.size()) {
          counter++;
        }
      }
      totals2.emplace_back(counter);
      group.clear();
    } else {
      all_answers += line;
      group.emplace_back(line);
    }
  }

  print("Part 1: {}\n", accumulate(totals.begin(), totals.end(), 0));
  print("Part 2: {}\n", accumulate(totals2.begin(), totals2.end(), 0));

  return 0;
}
