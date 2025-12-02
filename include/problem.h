#ifndef PROBLEM_H
#define PROBLEM_H

#include <filesystem>
#include <string>

class Problem {
public:
  virtual ~Problem() = default;

  virtual std::string solve() { return solve(""); }

  virtual std::string solve(std::filesystem::path path) = 0;
};

#endif // !PROBLEM_H
