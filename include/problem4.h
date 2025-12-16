#ifndef PROBLEM_4_H
#define PROBLEM_4_H
// IWYU pragma: always_keep

#include "problem.h"
#include "problems.h"

#include <filesystem>
#include <string>

class Problem4 : public Problem {
public:
  std::string solve() override;

  std::string solve(std::filesystem::path path) override;

  Problem4() = default;
  ~Problem4() override {};
};

REGISTER_CLASS(Problem4);

#endif // !PROBLEM_4_H
