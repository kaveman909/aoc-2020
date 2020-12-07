#include <algorithm>
#include <cassert>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <fmt/core.h>

using namespace std;
using namespace fmt;

int main(int argc, char *argv[]) {
  assert(argc == 2);

  const int MAX_LEN = 10;
  const int TARGET = 2020;

  ifstream in(argv[1]);
  vector<int> v;

  for (char buf[MAX_LEN]; in.getline(buf, MAX_LEN);) {
    v.emplace_back(stoi(buf));
  }

  // Since there's lots of large numbers that won't add to 2020, will be faster
  // in the long run if we sort the list first (I would think... though could be
  // wrong!)
  sort(v.begin(), v.end());
  bool found = false;

  for (const auto &i : v) {
    for (const auto &j : v) {
      for (const auto &k : v) {
        if (!found && ((j + k) == TARGET)) {
          print("Part 1: {}\n", j * k);
          found = true;
        } else if ((i + j + k) == TARGET) {
          print("Part 2: {}\n", i * j * k);
          return 0;
        }
      }
    }
  }

  return 1;
}
