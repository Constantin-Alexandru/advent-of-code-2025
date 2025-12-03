#include "problem2.h"

#include <cmath>
#include <cstdint>
#include <fstream>
#include <string>
#include <utility>

int count_digits(uint64_t number) {
  int count = 0;
  while (number > 0) {
    count++;
    number /= 10;
  }

  return count;
}

bool is_made_of_sequence(uint64_t number) {
  int digit_count = count_digits(number);
  bool answer = false;

  for (int digit = digit_count / 2; digit > 0 && answer == false; digit--) {
    uint64_t power_of_10 = std::pow(10, digit);

    uint64_t sequence = std::stol(std::to_string(number).substr(0, digit));
    uint64_t number_copy = std::stol(std::to_string(number).substr(digit));

    if ((std::size_t)count_digits(number_copy) !=
        std::to_string(number).substr(digit).size())
      continue;

    if (number_copy == 0)
      continue;

    while (number_copy > 0) {
      if (sequence != (number_copy % power_of_10)) {

        break;
      }
      number_copy = number_copy / power_of_10;
    }

    if (number_copy <= 0) {
      answer = true;
    }
  }
  return answer;
}

std::string Problem2::solve() { return this->solve("inputs/problem2.txt"); }

std::string Problem2::solve(std::filesystem::path path) {

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

  std::vector<std::pair<uint64_t, uint64_t>> ranges;

  uint64_t max_number = 0;

  for (std::string range; std::getline(reader, range, ',');) {
    uint64_t range_start = std::stol(range.substr(0, range.find('-')));
    uint64_t range_end = std::stol(range.substr(range.find('-') + 1));

    if (range_end > max_number)
      max_number = range_end;

    ranges.push_back(std::make_pair(range_start, range_end));
  }

  std::sort(ranges.begin(), ranges.end(),
            [](auto &left, auto &right) { return left.first < right.first; });

  uint64_t sum_invalid_ids = 0;
  uint64_t sum_invalid_ids2 = 0;

  for (const auto &[first, second] : ranges) {
    for (uint64_t number = first; number <= second; number++) {
      if (is_made_of_sequence(number)) {

        sum_invalid_ids2 += number;
      }

      int digit_count = count_digits(number);
      uint64_t half_count = digit_count / 2;

      uint64_t power_of_10 = std::pow(10, half_count);

      if (number % power_of_10 == number / power_of_10) {
        sum_invalid_ids += number;
      }
    }
  }

  return std::format(
      "Day 2\n\t- Part 1: Sum of invalid IDs is \x1b[1m{}\x1b[0m\n\t- "
      "Part 2: Sum of invalid IDs is \x1b[1m{}\x1b[0m",
      sum_invalid_ids, sum_invalid_ids2);
}
