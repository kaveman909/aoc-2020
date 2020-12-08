#include <fmt/core.h>
#include <fmt/ranges.h>

#include <cassert>
#include <regex>
#include <string>
#include <vector>

#include "aoc_util.h"

using namespace std;
using namespace fmt;

int main(int argc, char *argv[]) {
  assert(argc == 2);

  const auto in = process_input(argv[1]);
  const regex parse(R"((\d+)-(\d+) (\w): (\w+))");
  int password_counter = 0;
  int password_counter_2 = 0;

  for (const auto &line : in) {
    smatch m;
    regex_search(line, m, parse);
    const int lowest = stoi(m.str(1));
    const int highest = stoi(m.str(2));
    const char letter = m.str(3).c_str()[0];
    const string password = m.str(4);

    int letter_counter = 0;
    for (const auto &c : password) {
      if (c == letter) {
        letter_counter++;
      }
    }
    if ((letter_counter <= highest) && (letter_counter >= lowest)) {
      password_counter++;
    }

    const int &p1 = lowest;
    const int &p2 = highest;

    const bool p1_m = (password.c_str()[p1 - 1] == letter);
    const bool p2_m = (password.c_str()[p2 - 1] == letter);

    if (p1_m ^ p2_m) {
      password_counter_2++;
    }
  }

  print("Part 1: {}\n", password_counter);
  print("Part 2: {}\n", password_counter_2);

  return 0;
}
