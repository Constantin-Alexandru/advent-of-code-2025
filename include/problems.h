#ifndef PROBLEMS_H
#define PROBLEMS_H

#include "problem.h"

#include <algorithm>
#include <cstddef>
#include <functional>
#include <iterator>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class ProblemRegistry {
public:
  using Builder = std::function<std::unique_ptr<Problem>()>;

  static std::map<std::string, Builder> &getRegistry() {
    static std::map<std::string, Builder> registry;
    return registry;
  }

  static void registerClass(const std::string &name, Builder builder) {
    getRegistry()[name] = builder;
  }

  static std::unique_ptr<Problem> create(const std::string &name) {
    auto &registry = getRegistry();

    if (registry.find(name) != registry.end()) {
      return registry[name]();
    }
    return nullptr;
  }

  static std::size_t count() { return getRegistry().size(); }

  static std::vector<std::string> keys() {
    std::vector<std::string> keys;

    auto &registry = getRegistry();

    std::transform(
        registry.begin(), registry.end(), std::back_inserter(keys),
        [](const std::pair<std::string, Builder> &pair) { return pair.first; });

    return keys;
  }
};

struct Registrar {
  Registrar(const std::string &name, ProblemRegistry::Builder builder) {
    ProblemRegistry::registerClass(name, builder);
  }
};

#define REGISTER_CLASS(CLASS)                                                  \
  static Registrar registrar_##CLASS(                                          \
      #CLASS,                                                                  \
      []() -> std::unique_ptr<Problem> { return std::make_unique<CLASS>(); });

#endif // !PROBLEMS_H
