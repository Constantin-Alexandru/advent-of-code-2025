#include "problem3.h"

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <print>
#include <string>

int can_insert(std::vector<char> digits, char digit) {

  size_t i = 1;
  for (; i < digits.size(); i++) {
    if (digits[i] > digits[i - 1])
      return i - 1;
  }

  if (digits[i - 1] < digit)
    return i - 1;

  return -1;
};

std::string Problem3::solve() { return this->solve("inputs/problem3.txt"); }

std::string Problem3::solve(std::filesystem::path path) {

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

  uint64_t joltage = 0;
  uint64_t joltage2 = 0;
  for (std::string bank; std::getline(reader, bank);) {
    std::vector<char> digits(bank.size());

    std::transform(bank.begin(), bank.end(), digits.begin(),
                   [](const char ch) { return ch - '0'; });

    std::size_t index1 = 0, index2 = 1;

    for (std::size_t i = 2; i < digits.size(); i++) {
      if (digits[i] > digits[index1] && i != digits.size() - 1) {
        index1 = i;
        index2 = i + 1;
      } else if (digits[i] > digits[index2]) {
        index2 = i;
      }
    }

    std::vector<char> joltage_digits(digits.begin(), digits.begin() + 12);

    for (std::size_t i = 12; i < digits.size(); i++) {
      int index = can_insert(joltage_digits, digits[i]);
      if (index != -1) {
        joltage_digits.erase(joltage_digits.begin() + index);
        joltage_digits.push_back(digits[i]);
      }
    }

    uint64_t joltage_big = 0;

    for (const char &digit : joltage_digits) {
      joltage_big = joltage_big * 10 + digit;
    }

    joltage += (digits[index1] * 10 + digits[index2]);
    joltage2 += joltage_big;
  }

  return std::format(
      "Day 3\n\t- Part 1: Total output joltage is \x1b[1m{}\x1b[0m\n\t- "
      "Part 2: Total output joltage is \x1b[1m{}\x1b[0m",
      joltage, joltage2);
}
