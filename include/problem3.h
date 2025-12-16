#ifndef PROBLEM_3_H
#define PROBLEM_3_H
// IWYU pragma: always_keep

#include "problem.h"
#include "problems.h"

#include <filesystem>
#include <string>

class Problem3 : public Problem {
public:
  std::string solve() override;

  std::string solve(std::filesystem::path path) override;

  Problem3() = default;
  ~Problem3() override {};
};

REGISTER_CLASS(Problem3);

#endif // !PROBLEM_3_H
