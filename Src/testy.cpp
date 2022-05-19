#include "testy.h"

#include <vector>
#include <regex>
#include <string_view>

namespace testy {

static std::vector<function_base *> tests

void run_all() {
    std::fprintf(stdout, "Running %d tests.\n", tests.size());
    for (const auto* test : tests) {
        test->run();
    }
}

void run_match(const std::string_view& pattern) {
    std::regex name(pattern.data());
    for (const auto* test : tests) {
        if (std::regex_search(test->name, name)) {
            test->run();
        }
    }
}

constexpr test_function::test_function(const char* name, TestFunc fn) noexcept
    : name{ name }
    , fn{ fn } {
    tests.push_back(this);
}

void test_function::run() const {
    std::fprintf(stdout, "%s\n", name);
    fn();
}

}
