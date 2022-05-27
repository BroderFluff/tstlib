#pragma once
#ifndef TST_H
#define TST_H

#include <cstdio>
#include <cstdlib>
#include <string_view>

#if __has_include(<source_location>)
#   include <source_location>
    using std::source_location;
#elif __has_include(<experimental/source_location>)
#   include <experimental/source_location>
    using std::experimental::source_location;
#endif

#if __has_cpp_attribute(noreturn)
#   define NORETURN [[noreturn]]
#else
#   define NORETURN
#endif

inline const char* fail_fmt = "Failed!\n%s(%d): Assertion failed: (%s)\n";

#define UNIT_TEST(n) static tst::function n##_func(#n, n)
#define ASSERT_EQ(a, b) ASSERT_TRUE((a) == (b))
#define ASSERT_NEQ(a, b) ASSERT_TRUE((a) != (b))

#if defined(__cpp_lib_source_location) || defined(__cpp_lib_experimental_source_location)
#   define ASSERT_TRUE(expr) (void) ((expr) || (assertTrue(#expr)))
NORETURN inline bool assertTrue(const char* expr, const source_location& src = source_location::current()) {
    std::fprintf(stderr, fail_fmt, src.file_name(), src.line(), expr);
    std::exit(EXIT_FAILURE);
}
#else
#   define ASSERT_TRUE(expr) (void) ((expr) || (assertTrue(#expr, __FILE__, __LINE__)))
NORETURN inline bool assertTrue(const char* expr, const char* file, int line) {
    std::fprintf(stderr, fail_fmt, file, line, expr);
    std::exit(EXIT_FAILURE);
}
#endif

namespace tst {

void           run_all();
void           run_match(const std::string_view& pattern);

class function_base {
public:
                    function_base(const function_base&) noexcept = delete;
                    function_base(function_base&&) noexcept = delete;
                    virtual ~function_base() = default;

    function_base& operator=(const function_base&) noexcept = delete;
    function_base& operator=(function_base&&) noexcept = delete;

    void operator()() const { run(); }

    const char*     get_name() const { return name.data(); }

protected:
    explicit        function_base(std::string_view name) noexcept;
    virtual void    run() const = 0;

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
        std::fprintf(stdout, "%s...\t", get_name());
        fn();
    }

private:
    Fn fn;
};

}

#endif // TST_H
