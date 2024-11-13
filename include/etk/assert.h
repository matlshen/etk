#ifndef __LIBECPP_ASSERT_H_
#define __LIBECPP_ASSERT_H_

#include "etk/__assert/assert.h"
#include "etk/__config.h"

// Legacy macros
#define ASSERT_0(expr) ASSERT(expr == 0)
#define ASSERT_UNREACHABLE() ASSERT(0)

#endif // __LIBECPP_ASSERT_H_