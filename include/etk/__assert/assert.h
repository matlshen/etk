#ifndef __ETK___ASSERT_ASSERT_H_
#define __ETK___ASSERT_ASSERT_H_

// #include "etk/__assert/support.h"
#include "etk/__config.h"
#include "etk/print.h"

_ETK_BEGIN_NAMESPACE_ETK

// Assertion wrapper class
struct __Assert {
    static _ETK_API_INTERNAL void
    api_assert(int expr, const char* msg, const char* file, const char* line) {
        //__etk_assert(expr, msg, file, line);
        if (!expr) {
            etk::printf("Assertion failed: %s :%s: %s\n", msg, file, line);
        }
    }

    static _ETK_API_INTERNAL void api_expect(
        long expr,
        const char* op,
        long val,
        long expected,
        const char* file,
        const char* line) {
        // __etk_expect(expr, expected, val, op, file, line);
        if (!expr) {
            etk::printf("Expected %s%ld, got %ld :%s: %s\n",
                        op,
                        expected,
                        val,
                        file,
                        line);
        }
    }

    static _ETK_API_INTERNAL void api_assert_fail(
        int expr, const char* msg, const char* file, const char* line) {
        //__etk_conditional_abort(__etk_assert(expr, msg, file, line));
        bool condition = static_cast<bool>(expr);
        if (!condition) {
            etk::printf("Assertion failed: %s :%s: %s\n", msg, file, line);
            // TODO: Add platform-specific abort
        }
    }

    static _ETK_API_INTERNAL void api_expect_fail(
        long expr,
        const char* op,
        long val,
        long expected,
        const char* file,
        const char* line) {
        // __etk_conditional_abort(
        //     __etk_expect(expr, expected, val, op, file, line));
        bool condition = static_cast<bool>(expr);
        if (!condition) {
            etk::printf("Expected %s%ld, got %ld :%s: %s\n",
                        op,
                        expected,
                        val,
                        file,
                        line);
        }
    }
};

// Helper macros to temporarily store evaluated values
#define __ASSERT_EVAL(expected, val)                                           \
    {                                                                          \
        long __expected_val = static_cast<long>(expected);                     \
        long __got_val      = static_cast<long>(val);                          \
        (void)__expected_val;                                                  \
        (void)__got_val;
#define __ASSERT_EXPECTED __expected_val
#define __ASSERT_VAL __got_val
#define __ASSERT_EVAL_END }

_ETK_END_NAMESPACE_ETK

#endif // __ETK___ASSERT_ASSERT_H_