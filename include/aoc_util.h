#pragma once

#include <fstream>
#include <string>
#include <vector>

static const int MAX_LEN = 150;

std::vector<std::string> process_input(char *fpath);

template <typename T>
std::vector<T> process_input(char *fpath, T (*conv_f)(const std::string &)) {
  std::ifstream in(fpath);
  std::vector<T> v;

  for (char buf[MAX_LEN]; in.getline(buf, MAX_LEN);) {
    v.emplace_back(conv_f(buf));
  }

  return v;
}
