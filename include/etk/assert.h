#ifndef __LIBECPP_ASSERT_H_
#define __LIBECPP_ASSERT_H_

#include "etk/__assert/assert.h"
#include "etk/__config.h"

_ETK_BEGIN_NAMESPACE_ETK

/*
Abort the program. Call abort function directly.
*/
#ifndef ABORT
#    define ABORT() __etk_conditional_abort(false)
#endif
#ifndef ABORT_MSG
#    define ABORT_MSG(msg)                                                     \
        __etk_conditional_abort(etk::__Assert::api_assert(                     \
            false, msg, __FILE__, TO_STRING(__LINE__)))
#endif

/*
Assert expression is true
*/
#ifndef ASSERT
#    define ASSERT(expr)                                                       \
        etk::__Assert::api_assert(expr, "", __FILE__, TO_STRING(__LINE__))
#endif
#ifndef ASSERT_FAIL
#    define ASSERT_FAIL(expr)                                                  \
        etk::__Assert::api_assert_fail(expr, "", __FILE__, TO_STRING(__LINE__))
#endif

#ifndef ASSERT_MSG
#    define ASSERT_MSG(expr, msg)                                              \
        etk::__Assert::api_assert(expr, msg, __FILE__, TO_STRING(__LINE__))
#endif
#ifndef ASSERT_MSG_FAIL
#    define ASSERT_MSG_FAIL(expr, msg)                                         \
        etk::__Assert::api_assert_fail(expr, msg, __FILE__, TO_STRING(__LINE__))
#endif

/*
Assert statement is not reached
*/
#ifndef ASSERT_UNREACHABLE
#    define ASSERT_UNREACHABLE()                                               \
        etk::__Assert::api_assert(                                             \
            false, "Unreachable code", __FILE__, TO_STRING(__LINE__))
#endif
#ifndef ASSERT_UNREACHABLE_FAIL
#    define ASSERT_UNREACHABLE_FAIL()                                          \
        etk::__Assert::api_assert_fail(                                        \
            false, "Unreachable code", __FILE__, TO_STRING(__LINE__))
#endif

/*
Assert expression evaluates to 0
*/
#ifndef ASSERT_0
#    define ASSERT_0(expr)                                                     \
        __ASSERT_EVAL(0, expr);                                                \
        etk::__Assert::api_expect(                                             \
            __ASSERT_VAL == 0,                                                 \
            "== ",                                                             \
            __ASSERT_VAL,                                                      \
            0,                                                                 \
            __FILE__,                                                          \
            TO_STRING(__LINE__));                                              \
        __ASSERT_EVAL_END
#endif
#ifndef ASSERT_0_FAIL
#    define ASSERT_0_FAIL(expr)                                                \
        __ASSERT_EVAL(0, expr);                                                \
        etk::__Assert::api_expect_fail(                                        \
            __ASSERT_VAL == 0,                                                 \
            "== ",                                                             \
            __ASSERT_VAL,                                                      \
            0,                                                                 \
            __FILE__,                                                          \
            TO_STRING(__LINE__));                                              \
        __ASSERT_EVAL_END
#endif

/*
Assert expressions are equal
*/
#ifndef ASSERT_EQ
#    define ASSERT_EQ(expected, expr)                                          \
        __ASSERT_EVAL(expected, expr);                                         \
        etk::__Assert::api_expect(                                             \
            __ASSERT_VAL == __ASSERT_EXPECTED,                                 \
            "== ",                                                             \
            __ASSERT_VAL,                                                      \
            __ASSERT_EXPECTED,                                                 \
            __FILE__,                                                          \
            TO_STRING(__LINE__));                                              \
        __ASSERT_EVAL_END
#endif
#define ASSERT_EQ_FAIL(expected, expr)                                         \
    __ASSERT_EVAL(expected, expr);                                             \
    etk::__Assert::api_expect_fail(                                            \
        __ASSERT_VAL == __ASSERT_EXPECTED,                                     \
        "== ",                                                                 \
        __ASSERT_VAL,                                                          \
        __ASSERT_EXPECTED,                                                     \
        __FILE__,                                                              \
        TO_STRING(__LINE__));                                                  \
    __ASSERT_EVAL_END

/*
Assert expressions are not equal
*/
#ifndef ASSERT_NE
#    define ASSERT_NE(expected, expr)                                          \
        __ASSERT_EVAL(expected, expr);                                         \
        etk::__Assert::api_expect(                                             \
            __ASSERT_VAL != __ASSERT_EXPECTED,                                 \
            "!= ",                                                             \
            __ASSERT_VAL,                                                      \
            __ASSERT_EXPECTED,                                                 \
            __FILE__,                                                          \
            TO_STRING(__LINE__));                                              \
        __ASSERT_EVAL_END
#endif
#define ASSERT_NE_FAIL(expected, expr)                                         \
    __ASSERT_EVAL(expected, expr);                                             \
    etk::__Assert::api_expect_fail(                                            \
        __ASSERT_VAL != __ASSERT_EXPECTED,                                     \
        "!= ",                                                                 \
        __ASSERT_VAL,                                                          \
        __ASSERT_EXPECTED,                                                     \
        __FILE__,                                                              \
        TO_STRING(__LINE__));                                                  \
    __ASSERT_EVAL_END

/*
Assert val1 < val2
*/
#ifndef ASSERT_LT
#    define ASSERT_LT(val1, val2)                                              \
        __ASSERT_EVAL(val2, val1);                                             \
        etk::__Assert::api_expect(                                             \
            __ASSERT_VAL < __ASSERT_EXPECTED,                                  \
            "< ",                                                              \
            __ASSERT_VAL,                                                      \
            __ASSERT_EXPECTED,                                                 \
            __FILE__,                                                          \
            TO_STRING(__LINE__));                                              \
        __ASSERT_EVAL_END
#endif
#define ASSERT_LT_FAIL(val1, val2)                                             \
    __ASSERT_EVAL(val2, val1);                                                 \
    etk::__Assert::api_expect_fail(                                            \
        __ASSERT_VAL < __ASSERT_EXPECTED,                                      \
        "< ",                                                                  \
        __ASSERT_VAL,                                                          \
        __ASSERT_EXPECTED,                                                     \
        __FILE__,                                                              \
        TO_STRING(__LINE__));                                                  \
    __ASSERT_EVAL_END

/*
Assert val1 <= val2
*/
#ifndef ASSERT_LE
#    define ASSERT_LE(val1, val2)                                              \
        __ASSERT_EVAL(val2, val1);                                             \
        etk::__Assert::api_expect(                                             \
            __ASSERT_VAL <= __ASSERT_EXPECTED,                                 \
            "<= ",                                                             \
            __ASSERT_VAL,                                                      \
            __ASSERT_EXPECTED,                                                 \
            __FILE__,                                                          \
            TO_STRING(__LINE__));                                              \
        __ASSERT_EVAL_END
#endif
#define ASSERT_LE_FAIL(val1, val2)                                             \
    __ASSERT_EVAL(val2, val1);                                                 \
    etk::__Assert::api_expect_fail(                                            \
        __ASSERT_VAL <= __ASSERT_EXPECTED,                                     \
        "<= ",                                                                 \
        __ASSERT_VAL,                                                          \
        __ASSERT_EXPECTED,                                                     \
        __FILE__,                                                              \
        TO_STRING(__LINE__));                                                  \
    __ASSERT_EVAL_END

/*
Assert val1 > val2
*/
#ifndef ASSERT_GT
#    define ASSERT_GT(val1, val2)                                              \
        __ASSERT_EVAL(val2, val1);                                             \
        etk::__Assert::api_expect(                                             \
            __ASSERT_VAL > __ASSERT_EXPECTED,                                  \
            "> ",                                                              \
            __ASSERT_VAL,                                                      \
            __ASSERT_EXPECTED,                                                 \
            __FILE__,                                                          \
            TO_STRING(__LINE__));                                              \
        __ASSERT_EVAL_END
#endif
#define ASSERT_GT_FAIL(val1, val2)                                             \
    __ASSERT_EVAL(val2, val1);                                                 \
    etk::__Assert::api_expect_fail(                                            \
        __ASSERT_VAL > __ASSERT_EXPECTED,                                      \
        "> ",                                                                  \
        __ASSERT_VAL,                                                          \
        __ASSERT_EXPECTED,                                                     \
        __FILE__,                                                              \
        TO_STRING(__LINE__));                                                  \
    __ASSERT_EVAL_END

/*
Assert val1 >= val2
*/
#ifndef ASSERT_GE
#    define ASSERT_GE(val1, val2)                                              \
        __ASSERT_EVAL(val2, val1);                                             \
        etk::__Assert::api_expect(                                             \
            __ASSERT_VAL >= __ASSERT_EXPECTED,                                 \
            ">= ",                                                             \
            __ASSERT_VAL,                                                      \
            __ASSERT_EXPECTED,                                                 \
            __FILE__,                                                          \
            TO_STRING(__LINE__));                                              \
        __ASSERT_EVAL_END
#endif
#define ASSERT_GE_FAIL(val1, val2)                                             \
    __ASSERT_EVAL(val2, val1);                                                 \
    etk::__Assert::api_expect_fail(                                            \
        __ASSERT_VAL >= __ASSERT_EXPECTED,                                     \
        ">= ",                                                                 \
        __ASSERT_VAL,                                                          \
        __ASSERT_EXPECTED,                                                     \
        __FILE__,                                                              \
        TO_STRING(__LINE__));                                                  \
    __ASSERT_EVAL_END

#define STATIC_ASSERT(expr) static_assert(expr, "")
#define STATIC_ASSERT_MSG(expr, str) static_assert(expr, str)

_ETK_END_NAMESPACE_ETK

#endif // __LIBECPP_ASSERT_H_