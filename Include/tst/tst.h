#pragma once
#ifndef TST_H
#define TST_H

#include <cstdlib>
#include <string_view>

#if __has_include(<source_location>)
#include <source_location>
using source_location = std::source_location;
#elif __has_include(<experimental/source_location>)
#include <experimental/source_location>
using std::experimental::source_location;
#endif

#if __has_cpp_attribute(noreturn)
#define NORETURN [[noreturn]]
#else
#define NORETURN
#endif

#define UNIT_TEST(n) tst::function n##_func(#n, n)

#define ASSERT_EQ(a, b) ASSERT_TRUE((a) == (b))

#if defined(__cpp_lib_source_location) || defined(__cpp_lib_experimental_source_location)
#define ASSERT_TRUE(expr) (void) ((expr) || (assertTrue(#expr)))
NORETURN inline bool assertTrue(const char* expr, const source_location& src = source_location::current()) {
    std::fprintf(stderr, "%s(%d): Assertion failed: (%s)\n", src.file_name(), src.line(), expr);
    std::exit(EXIT_FAILURE);
}
#else
#define ASSERT_TRUE(expr) (void) ((expr) || (assertTrue(#expr, __FILE__, __LINE__)))
NORETURN inline bool assertTrue(const char* expr, const char* file, int line) {
    std::fprintf(stderr, "%s(%d): Assertion failed: (%s)\n", file, line, expr);
    std::exit(EXIT_FAILURE);
}
#endif

namespace tst {

void           run_all();
void           run_match(const std::string_view& pattern);

using pfn_test = void (*)();

class function_base {
public:
    explicit function_base(std::string_view name) noexcept;

    virtual ~function_base() = default;

    const char* get_name() const { return name.data(); }

    virtual void run() const = 0;

private:
    std::string_view name;
};

template <class Fn>
class function : public function_base {
public:
    function(std::string_view name, Fn fn) noexcept :
        function_base(name),
        fn{ fn } {
    }

    void run() const override {
        std::fprintf(stdout, "%s\n", get_name());
        fn();
    }

private:
    Fn fn;
};

#if 0
class test_function {
public:
    constexpr test_function(const char* name, pfn_test fn) noexcept;
    void run() const;

private:
    const char* test_name;
    pfn_test    fn;
};
#endif

}

#endif // TST_H
