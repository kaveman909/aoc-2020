#include <fmt/core.h>
#include <fmt/ranges.h>

#include <algorithm>
#include <array>
#include <boost/algorithm/string.hpp>
#include <cassert>
#include <numeric>
#include <regex>
#include <string>
#include <vector>

#include "aoc_util.h"

using namespace std;
using namespace fmt;

map<string, vector<string>> create_map(const vector<string> &rules) {
  map<string, vector<string>> output_map;

  for (const auto &rule : rules) {
    const regex r(R"((.*) bags contain (.*)\.)");
    smatch m;
    regex_match(rule, m, r);
    const auto &outer_bag_name = m.str(1);
    const auto &inner_bags_unparsed = m.str(2);
    vector<string> inner_bags;
    boost::split(inner_bags, inner_bags_unparsed,
                 [](char c) { return c == ','; });
    for (auto &inner_bag : inner_bags) {
      const regex r1(R"( ?\d+ (.*) bags?)");
      smatch m1;
      if (regex_match(inner_bag, m1, r1)) {
        const auto &inner_bag_name = m1.str(1);
        if (!output_map.contains(inner_bag_name)) {
          output_map[inner_bag_name] = vector<string>();
        }
        output_map[inner_bag_name].emplace_back(outer_bag_name);
      }
    }
  }
  return output_map;
}

void count_parents(const map<string, vector<string>> &bag_map,
                  const string &bag, vector<string> &bag_list) {
  if (bag_map.contains(bag) && !bag_map.at(bag).empty()) {
    for (const auto &parent : bag_map.at(bag)) {
      bag_list.emplace_back(parent);
      count_parents(bag_map, parent, bag_list);
    }
  }
}

int main(int argc, char *argv[]) {
  assert(argc == 2);

  const auto bag_map = create_map(process_input(argv[1]));

  vector<string> bag_list;
  count_parents(bag_map, "shiny gold", bag_list);
  ranges::sort(bag_list);
  auto [first, last] = ranges::unique(bag_list);
  bag_list.erase(first, last);

  print("Part 1: {}\n", bag_list.size());

  return 0;
}
