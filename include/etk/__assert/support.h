#ifndef _ETK___ASSERT_SUPPORT_H_
#define _ETK___ASSERT_SUPPORT_H_

#include "etk/__config.h"

/*
The library provides support for multiple implementations of assertion handling.
The following functionality must be provided by any implementation:


_ETK_BEGIN_NAMESPCE_ETK

bool __etk_assert(int expr, const char *msg,
    const char *file, const char *line);

bool __etk_expect(long expr, long expected, const char *msg,
    const char *file, const char *line);

void __etk_conditional_abort(bool condition);

_ETK_END_NAMESPCE_ETK
*/

#if defined(_ETK_HAS_ASSERT_API_LINUX)
#include "etk/__assert/support/linux.h"
#else
#error "No assert support API defined"
#endif

#endif // _ETK___ASSERT_SUPPORT_H_