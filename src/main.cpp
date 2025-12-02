#include "problem.h"
#include "problems.h"
#include <cstring>
#include <print>

void help(std::vector<std::string> &keys) {
  std::println("advent-of-code <problem> <path>");
  std::println("\t- <problem>: the problem to solve. Possible values:");
  std::println("\t\t- all: solve all problems using default path");
  for (const auto &key : keys) {
    std::println("\t\t - {} - solve {}", key, key);
  }
  std::println("\t- <path> (optional): path to the input file.");
  std::println("\t\t if <problem> is all, path will be ignored.");
}

void solve_problem(const char *name, const char *path = "") {
  std::unique_ptr<Problem> problem = ProblemRegistry::create(name);

  std::string output;

  if (strcmp(path, "") != 0) {
    output = problem->solve(path);
  } else {
    output = problem->solve();
  }

  std::println("{}", output);
}

int main(int argc, char *argv[]) {
  std::vector<std::string> keys = ProblemRegistry::keys();

  if (argc < 2) {
    help(keys);
    return -1;
  }

  if (std::find(keys.begin(), keys.end(), argv[1]) == keys.end() &&
      strcmp(argv[1], "all") != 0) {
    std::println("Invalid problem - found {}.", argv[1]);
    help(keys);
    return -1;
  }

  if (strcmp(argv[1], "all") == 0) {
    std::println("Solving all problems: \n");
    for (const auto &key : keys) {
      solve_problem(key.c_str());
    }
  } else {
    if (argc > 2) {
      solve_problem(argv[1], argv[2]);
    } else {
      solve_problem(argv[1]);
    }
  }

  return 0;
}
