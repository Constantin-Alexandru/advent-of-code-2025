#ifndef PROBLEM_1_H
#define PROBLEM_1_H
// IWYU pragma: always_keep

#include "problem.h"
#include "problems.h"

#include <filesystem>
#include <string>

class Problem1 : public Problem {
public:
  std::string solve() override;

  std::string
  solve(std::filesystem::path path = "inputs/problem1.txt") override;

  Problem1() = default;
  ~Problem1() override {};
};

REGISTER_CLASS(Problem1);

#endif // !PROBLEM_1_H
