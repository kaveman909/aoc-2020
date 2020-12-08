#include <fmt/core.h>
#include <fmt/ranges.h>

#include <cassert>
#include <regex>
#include <string>
#include <vector>

#include "aoc_util.h"

using namespace std;
using namespace fmt;
using namespace std::string_literals;

int main(int argc, char *argv[]) {
  assert(argc == 2);

  const auto in = process_input(argv[1]);
  const regex parse(R"((\d+)-(\d+) (\w): (\w+))");
  int password_counter = 0;

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
  }

  print("Part 1: {}\n", password_counter);

  return 0;
}
