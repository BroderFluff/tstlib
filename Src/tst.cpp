#include "tst.h"

#include <vector>
#include <regex>
#include <string_view>
#include <functional>

namespace tst {

static std::vector<function_base*> tests;

void run_all() {
    std::fprintf(stdout, "Running %zi tests.\n", tests.size());
    for (const auto *test : tests) {
        std::invoke(*test);
        std::puts("Success!");
    }
}

void run_match(const std::string_view& pattern) {
    const std::regex name(pattern.data());

    for (const auto& test : tests) {
        if (std::regex_search(test->get_name(), name)) {
            std::invoke(*test);
            std::puts("Success!");
        }
    }
}

function_base::function_base(std::string_view name) noexcept :
    name{ name } {
    tests.push_back(this);
}

}

static void T_TestTest() {
    ASSERT_EQ(1, 1);
}
UNIT_TEST(T_TestTest);

static void T_AAA() {
    ASSERT_EQ(0, 0);
    ASSERT_NEQ(8, 7);
}
UNIT_TEST(T_AAA);

int main(int argc, char* argv[]) {
    if (argc > 1) {
        for (int i = 1; i < argc; ++i) {
            tst::run_match(argv[i]);
        }
    } else {
        tst::run_all();
    }

    return EXIT_SUCCESS;
}
