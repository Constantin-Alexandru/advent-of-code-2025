#include "problem4.h"

#include <cstddef>
#include <fstream>
#include <numeric>
#include <string>

std::string Problem4::solve() { return this->solve("inputs/problem4.txt"); }

std::string Problem4::solve(std::filesystem::path path) {

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

  std::vector<std::vector<int>> neighbours;

  for (std::string line, previous_line = ""; std::getline(reader, line);
       previous_line = line) {
    std::vector<int> neighbour_line(line.size(), 0);

    for (size_t i = 0; i < line.size(); i++) {
      if (line[i] == '@') {
        if (i > 0 && line[i - 1] == '@') {
          neighbour_line[i - 1]++;
        }
        if (i < line.size() - 1 && line[i + 1] == '@') {
          neighbour_line[i + 1]++;
        }
        if (neighbours.size() > 0) {
          std::size_t prev_line_index = neighbours.size() - 1;
          if (previous_line[i] == '@') {
            neighbour_line[i]++;
            neighbours[prev_line_index][i]++;
          }

          if (i > 0 && previous_line[i - 1] == '@') {
            neighbour_line[i]++;
            neighbours[prev_line_index][i - 1]++;
          }
          if (i < line.size() - 1 && previous_line[i + 1] == '@') {
            neighbour_line[i]++;
            neighbours[prev_line_index][i + 1]++;
          }
        }
      } else {
        neighbour_line[i] = -1;
      }
    }

    neighbours.push_back(neighbour_line);
  }

  std::vector<int> rolls;

  for (const auto &neighbour_line : neighbours) {
    for (const auto &neighbours_count : neighbour_line) {
      rolls.push_back(neighbours_count < 4 && neighbours_count >= 0 ? 1 : 0);
    }
  }

  int rolls_count2 = 1;
  for (int count = -1, prev_count = -2; prev_count != 0;) {
    rolls_count2 += count;

    prev_count = count;
    count = 0;

    std::vector<std::vector<int>> neighbours_copy(neighbours.begin(),
                                                  neighbours.end());
    for (std::size_t i = 0; i < neighbours.size(); i++) {
      for (std::size_t j = 0; j < neighbours[i].size(); j++) {
        if (neighbours[i][j] < 4 && neighbours[i][j] >= 0) {
          neighbours_copy[i][j] = -1;
          count++;

          if (j > 0)
            neighbours_copy[i][j - 1]--;
          if (j < neighbours[i].size() - 1)
            neighbours_copy[i][j + 1]--;
          if (i > 0) {
            neighbours_copy[i - 1][j]--;

            if (j > 0) {
              neighbours_copy[i - 1][j - 1]--;
            }
            if (j < neighbours[i].size() - 1)
              neighbours_copy[i - 1][j + 1]--;
          }
          if (i < neighbours.size() - 1) {
            neighbours_copy[i + 1][j]--;

            if (j > 0) {
              neighbours_copy[i + 1][j - 1]--;
            }
            if (j < neighbours[i].size() - 1)
              neighbours_copy[i + 1][j + 1]--;
          }
        }
      }
    }

    neighbours = neighbours_copy;
  }

  int rolls_count = std::accumulate(rolls.begin(), rolls.end(), 0);
  return std::format("Day 4\n\t- Part 1: Number of rolls accessible is "
                     "\x1b[1m{}\x1b[0m\n\t- "
                     "Part 2: Number of rolls accessible is \x1b[1m{}\x1b[0m",
                     rolls_count, rolls_count2);
}
