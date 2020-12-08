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

  auto in = process_input(argv[1]);

  const auto width = in.front().size();
  vector<int> tree_counts;

  for (const int &incr : {1, 3, 5, 7}) {
    int col = 0;
    int tree_count = 0;

    for (const auto &row : in) {
      if (row[col] == '#') {
        tree_count++;
      }
      col = (col + incr) % width;
    }
    if (incr == 3) {
      print("Part 1: {}\n", tree_count);
    }
    tree_counts.emplace_back(tree_count);
  }

  int col = 0;
  int tree_count = 0;

  for (int i = 0; i < in.size(); i += 2) {
    if (in[i][col] == '#') {
      tree_count++;
    }
    col = (col + 1) % width;
  }
  tree_counts.emplace_back(tree_count);

  unsigned product = accumulate(tree_counts.begin(), tree_counts.end(), 1,
                                [](unsigned x, unsigned y) { return x * y; });

  print("Part 2: {}\n", product);

  return 0;
}
