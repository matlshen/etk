#ifndef __ETK___ASSERT_ASSERT_H_
#define __ETK___ASSERT_ASSERT_H_

#include "etk/__assert/support.h"
#include "etk/__config.h"

_ETK_BEGIN_NAMESPCE_ETK

// Assertion wrapper class
struct __Assert {
    static _ETK_API_INTERNAL void assert(int expr, const char *msg,
                                         const char *file, const char *line) {
        __etk_assert(expr, msg, file, line);
    }

    static _ETK_API_INTERNAL void expect(long expr, const char *op, long val,
                                         long expected, const char *file,
                                         const char *line) {
        __etk_expect(expr, expected, val, op, file, line);
    }

    static _ETK_API_INTERNAL void
    assert_fail(int expr, const char *msg, const char *file, const char *line) {
        __etk_conditional_abort(__etk_assert(expr, msg, file, line));
    }

    static _ETK_API_INTERNAL void expect_fail(long expr, const char *op,
                                              long val, long expected,
                                              const char *file,
                                              const char *line) {
        __etk_conditional_abort(
            __etk_expect(expr, expected, val, op, file, line));
    }
};

// Helper macros to temporarily store evaluated values
#define __ASSERT_EVAL(expected, val)                                           \
    {                                                                          \
        long __expected_val = static_cast<long>(expected);                     \
        long __got_val = static_cast<long>(val);
#define __ASSERT_EXPECTED __expected_val
#define __ASSERT_VAL __got_val
#define __ASSERT_EVAL_END }

_ETK_END_NAMESPCE_ETK

#endif // __ETK___ASSERT_ASSERT_H_