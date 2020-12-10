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

struct Passport {
  struct Year {
    int year;

    Year(string year_) : year(stoi(year_)) {}

    bool between(const int low, const int high) const {
      return (year >= low) && (year <= high);
    }
  };

  struct Height {
    int height;
    string unit;

    Height(string _height) {
      const regex r(R"((\d+)(cm|in))");
      smatch m;
      if (regex_search(_height, m, r)) {
        height = stoi(m.str(1));
        unit = m.str(2);
      } else {
        height = -1;
        unit = "cm";
      }
    }

    bool between(int low, int high) const {
      int _height = (unit == "in") ? std::round(height * 2.54f) : height;

      return (_height >= low) && (_height <= high);
    }
  };

  struct Hair {
    string color;

    Hair(string color_) : color(color_) {}

    bool valid() const {
      const regex r(R"(#[0-9a-f]{6})");
      return regex_search(color, r);
    }
  };

  struct Eye {
    string color;

    Eye(string color_) : color(color_) {}

    bool valid() const {
      const array color_list = {"amb", "blu", "brn", "gry",
                                "grn", "hzl", "oth"};
      return ranges::find(color_list, color) != color_list.end();
    }
  };

  struct PassId {
    string id;

    PassId(string id_) : id(id_) {}

    bool valid() const {
      const regex r(R"(\d{9})");
      return regex_match(id, r);
    }
  };

  Year byr;    // birth year
  Year iyr;    // issue year
  Year eyr;    // expiration year
  Height hgt;  // height
  Hair hcl;    // hair color
  Eye ecl;     // eye color
  PassId pid;  // passport id

  Passport(string byr_, string iyr_, string eyr_, string hgt_, string hcl_,
           string ecl_, string pid_)
      : byr(byr_),
        iyr(iyr_),
        eyr(eyr_),
        hgt(hgt_),
        hcl(hcl_),
        ecl(ecl_),
        pid(pid_) {}

  bool valid() const {
    return byr.between(1920, 2002) && iyr.between(2010, 2020) &&
           eyr.between(2020, 2030) && hgt.between(150, 193) && hcl.valid() &&
           ecl.valid() && pid.valid();
  }
};

vector<string> flatten_passport_list(const vector<string> &in) {
  vector<string> out;

  string passport;
  for (const auto &line : in) {
    if (line.empty()) {
      out.emplace_back(passport);
      passport = "";
    } else {
      passport += (line + " ");
    }
  }
  out.emplace_back(passport);

  return out;
}

int main(int argc, char *argv[]) {
  assert(argc == 2);

  const auto in = flatten_passport_list(process_input(argv[1]));

  constexpr array keys = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};

  int found{0};
  int found2{0};
  for (const auto &line : in) {
    int counter{0};
    vector<string> pi;
    for (const auto &key : keys) {
      if (const auto pos = line.find(key); pos != string::npos) {
        const auto end = line.find(' ', pos);
        pi.emplace_back(line.substr(pos + 4, end - (pos + 4)));
        counter++;
      }
    }
    if (counter == keys.size()) {
      found++;
      Passport passport(pi[0], pi[1], pi[2], pi[3], pi[4], pi[5], pi[6]);
      if (passport.valid()) {
        found2++;
      }
    }
  }

  print("Part 1: {}\n", found);
  print("Part 2: {}\n", found2);

  return 0;
}
