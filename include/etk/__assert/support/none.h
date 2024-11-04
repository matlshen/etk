#ifndef _ETK___ASSERT_SUPPORT_NONE_H_
#define _ETK___ASSERT_SUPPORT_NONE_H_

#include "etk/__config.h"

_ETK_BEGIN_NAMESPACE_ETK

inline _ETK_API_INTERNAL bool __etk_assert(int expr, const char *msg,
                                           const char *file, const char *line) {
    (void)expr;
    (void)msg;
    (void)file;
    (void)line;
    return true;
}

inline _ETK_API_INTERNAL bool __etk_expect(long expr, long expected, long val,
                                           const char *op, const char *file,
                                           const char *line) {
    (void)expr;
    (void)expected;
    (void)val;
    (void)op;
    (void)file;
    (void)line;
    return true;
}

inline _ETK_API_INTERNAL void __etk_conditional_abort(bool condition) {
    (void)condition;
}

_ETK_END_NAMESPACE_ETK

#endif // _ETK___ASSERT_SUPPORT_NONE_H_