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

auto create_maps(const vector<string> &rules) {
  map<string, vector<string>> output_map1;
  map<string, vector<pair<string, int>>> output_map2;

  for (const auto &rule : rules) {
    const regex r(R"((.*) bags contain (.*)\.)");
    smatch m;
    regex_match(rule, m, r);
    const auto &outer_bag_name = m.str(1);
    if (!output_map2.contains(outer_bag_name)) {
      output_map2[outer_bag_name] = vector<pair<string, int>>();
    }
    const auto &inner_bags_unparsed = m.str(2);
    vector<string> inner_bags;
    boost::split(inner_bags, inner_bags_unparsed,
                 [](char c) { return c == ','; });
    for (auto &inner_bag : inner_bags) {
      const regex r1(R"( ?(\d+) (.*) bags?)");
      smatch m1;
      if (regex_match(inner_bag, m1, r1)) {
        const auto inner_bag_count = stoi(m1.str(1));
        const auto &inner_bag_name = m1.str(2);
        if (!output_map1.contains(inner_bag_name)) {
          output_map1[inner_bag_name] = vector<string>();
        }
        output_map1[inner_bag_name].emplace_back(outer_bag_name);
        output_map2[outer_bag_name].emplace_back(
            pair{inner_bag_name, inner_bag_count});
      }
    }
  }
  return pair{output_map1, output_map2};
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

int count_bags(const map<string, vector<pair<string, int>>> &bag_map,
               const string &bag) {
  int sum = 0;
  for (const auto &child : bag_map.at(bag)) {
    sum += ((count_bags(bag_map, child.first) * child.second) + child.second);
  }
  return sum;
}

int main(int argc, char *argv[]) {
  assert(argc == 2);

  const auto [bag_map1, bag_map2] = create_maps(process_input(argv[1]));

  vector<string> bag_list;
  count_parents(bag_map1, "shiny gold", bag_list);
  ranges::sort(bag_list);
  auto [first, last] = ranges::unique(bag_list);
  bag_list.erase(first, last);

  print("Part 1: {}\n", bag_list.size());
  print("Part 2: {}\n", count_bags(bag_map2, "shiny gold"));

  return 0;
}
