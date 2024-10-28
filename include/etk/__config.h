#ifndef __LIBEXPP___CONFIG_H_
#define __LIBEXPP___CONFIG_H_

#define _ETK_BEGIN_NAMESPACE_ETK namespace etk {
#define _ETK_END_NAMESPACE_ETK }

#define _ETK_API_INTERNAL __attribute__((visibility("hidden")))

// Utility macros
#define STRINGIFY(x) #x
#define TO_STRING(x) STRINGIFY(x)

// Platform specific configuration
#define _ETK_HAS_ASSERT_API_LINUX
// #define _ETK_HAS_THREAD_API_NONE
#define _ETK_HAS_THREAD_API_PTHREAD
// #define _ETK_HAS_THREAD_API_THREADX

// Library configuration
#define _ETK_THREAD_FUNC_MAX_SIZE 64

#endif // __LIBEXPP___CONFIG_H_