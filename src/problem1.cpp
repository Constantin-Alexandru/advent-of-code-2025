#include "problem1.h"

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <string>

int wrap(int value, int min, int max) {
  int range_size = max - min + 1;

  if (value < min)
    value += range_size * ((min - value) / range_size + 1);

  return min + (value - min) % range_size;
}

int wrap_count(int value, int min, int max) {
  int range_size = max - min + 1;
  int count = 0;

  if (value <= min) {
    count = (min + std::abs(value)) / range_size + 1;
  }

  if (value > max) {
    count = (min + value) / range_size;
  }

  return count;
}

std::string Problem1::solve() { return this->solve("inputs/problem1.txt"); }

std::string Problem1::solve(std::filesystem::path path) {

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

  int dial = 50;
  int secret = 0;
  int secret2 = 0;

  for (std::string rotation; std::getline(reader, rotation);) {
    char direction = rotation[0];
    int rotate = std::stoi(rotation.substr(1).c_str());

    if (dial == 0 && direction == 'L')
      secret2 -= 1;

    dial = direction == 'L' ? dial - rotate : dial + rotate;
    secret2 += wrap_count(dial, 0, 99);
    dial = wrap(dial, 0, 99);
    secret = dial == 0 ? secret + 1 : secret;
  }

  return std::format("Day 1\n\t- Part 1: Password is \x1b[1m{}\x1b[0m\n\t- "
                     "Part 2: Password is \x1b[1m{}\x1b[0m",
                     secret, secret2);
}
