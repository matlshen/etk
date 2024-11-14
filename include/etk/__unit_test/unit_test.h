#ifndef _ETK___UNIT_TEST_UNIT_TEST_H_
#define _ETK___UNIT_TEST_UNIT_TEST_H_

#include "etk/__print/print.h"
#include <initializer_list>
#include <tuple>

_ETK_BEGIN_NAMESPACE_ETK

using _test_element = std::tuple<const char*, void (*)()>;
using _test_suite   = std::initializer_list<_test_element>;

inline int __num_tests                 = 0;
inline int __num_passing               = 0;
inline int __num_failing               = 0;
inline const char* __current_test_name = nullptr;
inline bool __test_failed              = false;

#define PLURALIZE(n) (n == 1 ? "test" : "tests")

#define TEST_SUITE_START(suite_name)                                           \
    etk::_test_suite suite_name = {{"empty", []() {}

#define TEST(test_name)                                                        \
    }                                                                          \
    , {                                                                        \
#        test_name, []()

#define TEST_SUITE_END(suite_name)                                             \
    }                                                                          \
    }                                                                          \
    ;

#define RUN_TEST_SUITE(suite_name)                                             \
    etk::printf("=== %s ===\n", #suite_name);                                  \
    for (size_t test_idx = 1; test_idx < suite_name.size(); test_idx++) {      \
        auto test = suite_name.begin() + test_idx;                             \
        etk::printf(" -> %s", std::get<0>(*test));                             \
        etk::__num_tests++;                                                    \
        etk::__test_failed       = false;                                      \
        etk::__current_test_name = std::get<0>(*test);                         \
        std::get<1> (*test)();                                                 \
        if (etk::__test_failed) {                                              \
            etk::__num_failing++;                                              \
        } else {                                                               \
            etk::printf(" >>> passed\n");                                      \
            etk::__num_passing++;                                              \
        }                                                                      \
    }

#define CHECK(expr)                                                            \
    if (!(expr)) {                                                             \
        etk::printf("\n\tTest \"%s\" failed at line %d: %s",                   \
                    etk::__current_test_name,                                  \
                    __LINE__,                                                  \
                    #expr);                                                    \
        etk::__test_failed = true;                                             \
    }

inline void test_report() {
    if (__num_failing == 0) {
        etk::printf("\n\nAll tests pass! (>^o^)>\n");
    } else {
        etk::printf(
            "\n\n%d %s failed :(\n", __num_failing, PLURALIZE(__num_failing));
    }
    etk::printf("\n%d %s, %d passing, %d failing\n",
                __num_tests,
                PLURALIZE(__num_tests),
                __num_passing,
                __num_failing);
}

_ETK_END_NAMESPACE_ETK

#endif // _ETK___UNIT_TEST_UNIT_TEST_H_