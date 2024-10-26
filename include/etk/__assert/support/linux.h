#ifndef __LIBECPP___ASSERT_SUPPORT_LINUX_H_
#define __LIBECPP___ASSERT_SUPPORT_LINUX_H_

#include "etk/__config.h"
#include <stdio.h>
#include <stdlib.h>

_ETK_BEGIN_NAMESPACE_ETK

inline _ETK_API_INTERNAL bool __etk_assert(int expr, const char *msg,
                                           const char *file, const char *line) {
    if (!expr) {
        fprintf(stderr, "Assertion failed: %s :%s: %s\n", msg, file, line);
    }
    return static_cast<bool>(expr);
}

inline _ETK_API_INTERNAL bool __etk_expect(long expr, long expected, long val,
                                           const char *op, const char *file,
                                           const char *line) {
    if (!expr) {
        fprintf(stderr, "Expected %s%ld, got %ld :%s: %s\n", op, expected, val,
                file, line);
    }
    return static_cast<bool>(expr);
}

inline _ETK_API_INTERNAL void __etk_conditional_abort(bool condition) {
    if (!condition) {
        abort();
    }
}

_ETK_END_NAMESPACE_ETK

#endif // __LIBECPP___ASSERT_SUPPORT_LINUX_H_