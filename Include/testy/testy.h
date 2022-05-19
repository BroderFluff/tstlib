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

#define UNIT_TEST(n) testorosso::TestFunction n##_func(#n, n)

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

namespace testy {

void           run_all();
void           run_match(const std::string_view& pattern);

using pfn_test = void (*)();

class function_base {
public:
    virtual ~function_base() = default;

    virtual void run() = 0;
};

template <class Fn>
class function : public function_base {
public:
    function(std::string_view name, Fn fn) noexcept :
        name{ name },
        fn{ fn } {
    }

    void run() override {
        std::fprintf(stdout, "%s\n", name.data());
        fn();
    }

private:
    std::string_view name;
    Fn fn;
};

class test_function {
public:
    constexpr test_function(const char* name, TestFunc fn) noexcept;
    void run() const;

private:
    const char* test_name;
    pfn_test    fn;
};

}
