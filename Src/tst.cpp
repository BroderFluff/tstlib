#include "tst.h"

#include <vector>
#include <regex>
#include <string_view>

namespace tst {

static std::vector<function_base*> tests;

void run_all() {
    std::fprintf(stdout, "Running %d tests.\n", tests.size());
    for (const auto* test : tests) {
        test->run();
    }
}

void run_match(const std::string_view& pattern) {
    std::regex name(pattern.data());

    for (const auto* test : tests) {
        if (std::regex_search(test->get_name(), name)) {
            test->run();
        }
    }
}

function_base::function_base(std::string_view name) noexcept :
    name{ name } {

    tests.push_back(this);

}

#if 0
constexpr test_function::test_function(const char* name, pfn_test fn) noexcept
    , fn{ fn } {
    tests.push_back(this);
}

void test_function::run() const {
    std::fprintf(stdout, "%s\n", get_name());
    fn();
}
#endif

}

static void T_TestTest() {
    ASSERT_EQ(1, 1);
}
UNIT_TEST(T_TestTest);

int main(int argc, char* argv[]) {
    if (argc > 1) {
        tst::run_match(argv[1]);
    } else {
        tst::run_all();
    }

    return EXIT_SUCCESS;
}
