#include "aoc_util.h"

std::vector<std::string> process_input(char* fpath) {
  const int MAX_LEN = 100;
  std::ifstream in(fpath);
  std::vector<std::string> v;

  for (char buf[MAX_LEN]; in.getline(buf, MAX_LEN);) {
    v.emplace_back(buf);
  }

  return v;
}
