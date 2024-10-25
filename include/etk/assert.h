#ifndef __LIBECPP_ASSERT_H_
#define __LIBECPP_ASSERT_H_

#include "etk/__assert/assert.h"
#include "etk/__config.h"

_ETK_BEGIN_NAMESPCE_ETK

/*
Abort the program. Call abort function directly.
*/
#define ABORT() __etk_conditional_abort(false)
#define ABORT_MSG(msg)                                                         \
    __etk_conditional_abort(                                                   \
        etk::__Assert::assert(false, msg, __FILE__, TO_STRING(__LINE__)))

/*
Assert expression is true
*/
#define ASSERT(expr)                                                           \
    etk::__Assert::assert(expr, "", __FILE__, TO_STRING(__LINE__))
#define ASSERT_FAIL(expr)                                                      \
    etk::__Assert::assert_fail(expr, "", __FILE__, TO_STRING(__LINE__))

#define ASSERT_MSG(expr, msg)                                                  \
    etk::__Assert::assert(expr, msg, __FILE__, TO_STRING(__LINE__))
#define ASSERT_MSG_FAIL(expr, msg)                                             \
    etk::__Assert::assert_fail(expr, msg, __FILE__, TO_STRING(__LINE__))

/*
Assert statement is not reached
*/
#define ASSERT_UNREACHABLE()                                                   \
    etk::__Assert::assert(false, "Unreachable code", __FILE__,                 \
                          TO_STRING(__LINE__))
#define ASSERT_UNREACHABLE_FAIL()                                              \
    etk::__Assert::assert_fail(false, "Unreachable code", __FILE__,            \
                               TO_STRING(__LINE__))

/*
Assert expression evaluates to 0
*/
#define ASSERT_0(expr)                                                         \
    __ASSERT_EVAL(0, expr);                                                    \
    etk::__Assert::expect(__ASSERT_VAL == 0, "== ", __ASSERT_VAL, 0, __FILE__, \
                          TO_STRING(__LINE__));                                \
    __ASSERT_EVAL_END
#define ASSERT_0_FAIL(expr)                                                    \
    __ASSERT_EVAL(0, expr);                                                    \
    etk::__Assert::expect_fail(__ASSERT_VAL == 0, "== ", __ASSERT_VAL, 0,      \
                               __FILE__, TO_STRING(__LINE__));                 \
    __ASSERT_EVAL_END

/*
Assert expressions are equal
*/
#define ASSERT_EQ(expected, expr)                                              \
    __ASSERT_EVAL(expected, expr);                                             \
    etk::__Assert::expect(__ASSERT_VAL == __ASSERT_EXPECTED,                   \
                          "== ", __ASSERT_VAL, __ASSERT_EXPECTED, __FILE__,    \
                          TO_STRING(__LINE__));                                \
    __ASSERT_EVAL_END
#define ASSERT_EQ_FAIL(expected, expr)                                         \
    __ASSERT_EVAL(expected, expr);                                             \
    etk::__Assert::expect_fail(__ASSERT_VAL == __ASSERT_EXPECTED,              \
                               "== ", __ASSERT_VAL, __ASSERT_EXPECTED,         \
                               __FILE__, TO_STRING(__LINE__));                 \
    __ASSERT_EVAL_END

/*
Assert expressions are not equal
*/
#define ASSERT_NE(expected, expr)                                              \
    __ASSERT_EVAL(expected, expr);                                             \
    etk::__Assert::expect(__ASSERT_VAL != __ASSERT_EXPECTED,                   \
                          "!= ", __ASSERT_VAL, __ASSERT_EXPECTED, __FILE__,    \
                          TO_STRING(__LINE__));                                \
    __ASSERT_EVAL_END
#define ASSERT_NE_FAIL(expected, expr)                                         \
    __ASSERT_EVAL(expected, expr);                                             \
    etk::__Assert::expect_fail(__ASSERT_VAL != __ASSERT_EXPECTED,              \
                               "!= ", __ASSERT_VAL, __ASSERT_EXPECTED,         \
                               __FILE__, TO_STRING(__LINE__));                 \
    __ASSERT_EVAL_END

/*
Assert val1 < val2
*/
#define ASSERT_LT(val1, val2)                                                  \
    __ASSERT_EVAL(val2, val1);                                                 \
    etk::__Assert::expect(__ASSERT_VAL < __ASSERT_EXPECTED, "< ",              \
                          __ASSERT_VAL, __ASSERT_EXPECTED, __FILE__,           \
                          TO_STRING(__LINE__));                                \
    __ASSERT_EVAL_END
#define ASSERT_LT_FAIL(val1, val2)                                             \
    __ASSERT_EVAL(val2, val1);                                                 \
    etk::__Assert::expect_fail(__ASSERT_VAL < __ASSERT_EXPECTED, "< ",         \
                               __ASSERT_VAL, __ASSERT_EXPECTED, __FILE__,      \
                               TO_STRING(__LINE__));                           \
    __ASSERT_EVAL_END

/*
Assert val1 <= val2
*/
#define ASSERT_LE(val1, val2)                                                  \
    __ASSERT_EVAL(val2, val1);                                                 \
    etk::__Assert::expect(__ASSERT_VAL <= __ASSERT_EXPECTED,                   \
                          "<= ", __ASSERT_VAL, __ASSERT_EXPECTED, __FILE__,    \
                          TO_STRING(__LINE__));                                \
    __ASSERT_EVAL_END
#define ASSERT_LE_FAIL(val1, val2)                                             \
    __ASSERT_EVAL(val2, val1);                                                 \
    etk::__Assert::expect_fail(__ASSERT_VAL <= __ASSERT_EXPECTED,              \
                               "<= ", __ASSERT_VAL, __ASSERT_EXPECTED,         \
                               __FILE__, TO_STRING(__LINE__));                 \
    __ASSERT_EVAL_END

/*
Assert val1 > val2
*/
#define ASSERT_GT(val1, val2)                                                  \
    __ASSERT_EVAL(val2, val1);                                                 \
    etk::__Assert::expect(__ASSERT_VAL > __ASSERT_EXPECTED, "> ",              \
                          __ASSERT_VAL, __ASSERT_EXPECTED, __FILE__,           \
                          TO_STRING(__LINE__));                                \
    __ASSERT_EVAL_END
#define ASSERT_GT_FAIL(val1, val2)                                             \
    __ASSERT_EVAL(val2, val1);                                                 \
    etk::__Assert::expect_fail(__ASSERT_VAL > __ASSERT_EXPECTED, "> ",         \
                               __ASSERT_VAL, __ASSERT_EXPECTED, __FILE__,      \
                               TO_STRING(__LINE__));                           \
    __ASSERT_EVAL_END

/*
Assert val1 >= val2
*/
#define ASSERT_GE(val1, val2)                                                  \
    __ASSERT_EVAL(val2, val1);                                                 \
    etk::__Assert::expect(__ASSERT_VAL >= __ASSERT_EXPECTED,                   \
                          ">= ", __ASSERT_VAL, __ASSERT_EXPECTED, __FILE__,    \
                          TO_STRING(__LINE__));                                \
    __ASSERT_EVAL_END
#define ASSERT_GE_FAIL(val1, val2)                                             \
    __ASSERT_EVAL(val2, val1);                                                 \
    etk::__Assert::expect_fail(__ASSERT_VAL >= __ASSERT_EXPECTED,              \
                               ">= ", __ASSERT_VAL, __ASSERT_EXPECTED,         \
                               __FILE__, TO_STRING(__LINE__));                 \
    __ASSERT_EVAL_END

#define STATIC_ASSERT(expr) static_assert(expr, "")
#define STATIC_ASSERT_MSG(expr, str) static_assert(expr, str)

_ETK_END_NAMESPCE_ETK

#endif // __LIBECPP_ASSERT_H_