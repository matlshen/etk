#ifndef __LIBEXPP___CONFIG_H_
#define __LIBEXPP___CONFIG_H_

/**
 * Assert configuations
 */
// #define _ETK_HAS_ASSERT_API_NONE
#define _ETK_HAS_ASSERT_API_LINUX

/**
 * Logger configuations
 * Currently supported logging APIs:
 * - None
 * - RTT
 */
#define _ETK_HAS_LOG_API_NONE
// #define _ETK_HAS_LOG_API_RTT

/**
 * Threading configuations
 * Currently supported threading APIs:
 * - None
 * - Pthread
 * - ThreadX
 */
// # define _ETK_HAS_THREAD_API_NONE
// # define _ETK_HAS_THREAD_API_PTHREAD
# define _ETK_HAS_THREAD_API_APPLE
// # define _ETK_HAS_THREAD_API_THREADX

#define _ETK_BEGIN_NAMESPACE_ETK namespace etk {
#define _ETK_END_NAMESPACE_ETK }

#define _ETK_API_INTERNAL __attribute__((visibility("hidden")))

// Utility macros
#define STRINGIFY(x) #x
#define TO_STRING(x) STRINGIFY(x)

# if defined(_ETK_HAS_THREAD_API_PTHREAD)
#   define _ETK_HAS_NATIVE_MUTEX
#   define _ETK_HAS_NATIVE_SEMAPHORE
#   define _ETK_HAS_NATIVE_CONDVAR
//#   define _ETK_HAS_NATIVE_EVTFLG
//#   define _ETK_HAS_NATIVE_TIMER
// #   define _ETK_HAS_NATIVE_MQUEUE
# elif defined(_ETK_HAS_THREAD_API_APPLE)
#   define _ETK_HAS_NATIVE_MUTEX
// #   define _ETK_HAS_NATIVE_SEMAPHORE
#   define _ETK_HAS_NATIVE_CONDVAR
//#   define _ETK_HAS_NATIVE_EVTFLG
//#   define _ETK_HAS_NATIVE_TIMER
// #   define _ETK_HAS_NATIVE_MQUEUE
# elif defined(_ETK_HAS_THREAD_API_THREADX)
#   define _ETK_HAS_NATIVE_MUTEX
#   define _ETK_HAS_NATIVE_SEMAPHORE
//#   define _ETK_HAS_NATIVE_CONDVAR
#   define _ETK_HAS_NATIVE_EVTFLG
#   define _ETK_HAS_NATIVE_TIMER
#   define _ETK_HAS_NATIVE_MQUEUE
# endif

# define _ETK_THREAD_FUNC_MAX_SIZE 64

#endif // __LIBEXPP___CONFIG_H_