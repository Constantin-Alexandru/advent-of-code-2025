#ifndef PROBLEM_5_H
#define PROBLEM_5_H
// IWYU pragma: always_keep

#include "problem.h"
#include "problems.h"

#include <filesystem>
#include <string>

class Problem5 : public Problem {
public:
  std::string solve() override;

  std::string solve(std::filesystem::path path) override;

  Problem5() = default;
  ~Problem5() override {};
};

REGISTER_CLASS(Problem5);

#endif // !PROBLEM_5_H
