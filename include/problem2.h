#ifndef PROBLEM_2_H
#define PROBLEM_2_H
// IWYU pragma: always_keep

#include "problem.h"
#include "problems.h"

#include <filesystem>
#include <string>

class Problem2 : public Problem {
public:
  std::string solve() override;

  std::string solve(std::filesystem::path path) override;

  Problem2() = default;
  ~Problem2() override {};
};

REGISTER_CLASS(Problem2);

#endif // !PROBLEM_2_H
