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

struct Prog {
  int pc = 0;
  int acc = 0;
  vector<string> instrs;

  Prog(vector<string> instrs_) : instrs(instrs_) {}

  void step() {
    // parse instruction
    const auto instr = instrs[pc];
    const auto op = instr.substr(0, 3);
    const auto arg = stoi(instr.substr(4));

    // execute operation
    if (op == "acc") {
      acc += arg;
      pc += 1;
    } else if (op == "jmp") {
      pc += arg;
    } else {
      pc += 1;
    }
  }
};

int main(int argc, char *argv[]) {
  assert(argc == 2);

  auto instrs = process_input(argv[1]);
  Prog p{instrs};
  vector<int> visited;

  while (1) {
    visited.emplace_back(p.pc);

    p.step();

    // determine if we've 'been here before'
    if (ranges::find(visited, p.pc) != visited.end()) {
      break;
    }
  }

  print("Part 1: {}\n", p.acc);

  vector<string>::iterator it = instrs.begin();

  auto line = ranges::find_if(it, instrs.end(), [&](string s) {
    return s.find("nop") != string::npos;
  });
  it = line;
  if (it != instrs.end()) {
    (*it).replace(0, 3, "jmp");
  }

  print("{}\n", *it);

  return 0;
}
