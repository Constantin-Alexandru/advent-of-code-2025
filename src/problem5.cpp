#include "problem5.h"

#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <set>
#include <string>
#include <utility>

std::vector<std::pair<uint64_t, uint64_t>>
compress_ranges(std::vector<std::pair<uint64_t, uint64_t>> ranges) {

  std::vector<std::pair<uint64_t, uint64_t>> compressed_ranges{};
  bool compressed = true;

  while (compressed) {
    compressed = false;
    for (const auto &range : ranges) {
      uint64_t range_start = range.first, range_end = range.second;
      auto overlapping_range = std::find_if(
          compressed_ranges.begin(), compressed_ranges.end(),
          [&range_start, &range_end](auto &range) {
            return (range.first <= range_start &&
                    range_start <= range.second) ||
                   (range.first <= range_end && range_end <= range.second);
          });

      if (overlapping_range != compressed_ranges.end()) {
        compressed = true;
        if ((*overlapping_range).first <= range_start &&
            (*overlapping_range).second < range_end) {
          (*overlapping_range).second = range_end;
        } else if (range_start < (*overlapping_range).first) {
          (*overlapping_range).first = range_start;
        }
      } else {
        compressed_ranges.push_back(range);
      }
    }

    if (compressed) {
      ranges = compressed_ranges;
      compressed_ranges.resize(0);
    }
  }

  std::set<std::pair<uint64_t, uint64_t>> final_ranges(ranges.begin(),
                                                       ranges.end());

  return std::vector<std::pair<uint64_t, uint64_t>>(final_ranges.begin(),
                                                    final_ranges.end());
}

std::string Problem5::solve() { return this->solve("inputs/problem5.txt"); }

std::string Problem5::solve(std::filesystem::path path) {

  namespace fs = std::filesystem;

  if (!fs::exists(path)) {
    return std::format("\x1b[31m[ERROR]: File {} could not be found.\x1b[0m",
                       path.c_str());
  }

  std::ifstream reader(path);

  if (!reader.is_open()) {
    return std::format("\x1b[1m[ERROR]: File {} could not be loaded.\x1b[0m",
                       path.c_str());
  }

  std::vector<std::pair<uint64_t, uint64_t>> fresh_ingredients;
  for (std::string line; std::getline(reader, line) && line != "";) {
    uint64_t range_start = atol(line.substr(0, line.find('-')).c_str());
    uint64_t range_end = atol(line.substr(line.find('-') + 1).c_str());

    fresh_ingredients.push_back(std::make_pair(range_start, range_end));
  }

  fresh_ingredients = compress_ranges(fresh_ingredients);
  // std::sort(fresh_ingredients.begin(), fresh_ingredients.end());

  uint64_t fresh_count = 0;
  for (std::string line; std::getline(reader, line) && line != "";) {
    uint64_t ingredient_id = atol(line.c_str());

    bool is_valid =
        std::accumulate(fresh_ingredients.begin(), fresh_ingredients.end(),
                        false, [&ingredient_id](bool result, auto &range) {
                          return result || (range.first <= ingredient_id &&
                                            ingredient_id <= range.second);
                        });

    fresh_count += is_valid ? 1 : 0;
  }

  uint64_t valid_ids_count = 0;
  for (const auto &range : fresh_ingredients) {
    valid_ids_count += (range.second - range.first + 1);
  }

  return std::format("Day 5\n\t- Part 1: Number of fresh ingredients is "
                     "\x1b[1m{}\x1b[0m\n\t- "
                     "Part 2: Number of valid ids is \x1b[1m{}\x1b[0m",
                     fresh_count, valid_ids_count);
}
