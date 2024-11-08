#ifndef __LIBEXPP___CONFIG_H_
#define __LIBEXPP___CONFIG_H_

/**
 * Print configuations
 * Currently supported print APIs:
 * - None
 * - Stdio, internally uses vprintf()
 * - RTT, internally uses SEGGER_rtt_vprintf()
 */
#define _ETK_HAS_PRINT_API_STDIO
// #define _ETK_HAS_PRINT_API_RTT

/**
 * Memory management configurations
 * Currently supported memory management APIs:
 * - None
 * - Stdlib, standard C memory management API
 * - ThreadX, tx_byte_pool API
 */
#define _ETK_HEAP_SIZE 4096
// #define _ETK_HAS_MEMORY_API_NONE
#define _ETK_HAS_MEMORY_API_STDLIB
// #define _ETK_HAS_MEMORY_API_THREADX

/**
 * Threading configuations
 * Currently supported threading APIs:
 * - None
 * - Pthread, standard POSIX threading API
 * - Apple, non-standard semaphore implementation
 * - ThreadX
 */
// # define _ETK_HAS_THREAD_API_NONE
#define _ETK_HAS_THREAD_API_PTHREAD
// #define _ETK_HAS_THREAD_API_APPLE
// # define _ETK_HAS_THREAD_API_THREADX

///////////// Shouldn't need to modify anything below this line /////////////

#define _ETK_BEGIN_NAMESPACE_ETK namespace etk {
#define _ETK_END_NAMESPACE_ETK }

#define _ETK_API_INTERNAL __attribute__((visibility("hidden")))

// Utility macros
#define STRINGIFY(x) #x
#define TO_STRING(x) STRINGIFY(x)

#if defined(_ETK_HAS_THREAD_API_PTHREAD)
#    define _ETK_HAS_NATIVE_MUTEX
#    define _ETK_HAS_NATIVE_SEMAPHORE
#    define _ETK_HAS_NATIVE_CONDVAR
// #   define _ETK_HAS_NATIVE_EVTFLG
// #   define _ETK_HAS_NATIVE_TIMER
// #   define _ETK_HAS_NATIVE_MQUEUE
#    define _ETK_HAS_NATIVE_TIMER
#elif defined(_ETK_HAS_THREAD_API_APPLE)
#    define _ETK_HAS_NATIVE_MUTEX
// #   define _ETK_HAS_NATIVE_SEMAPHORE
#    define _ETK_HAS_NATIVE_CONDVAR
// #   define _ETK_HAS_NATIVE_EVTFLG
// #   define _ETK_HAS_NATIVE_TIMER
// #   define _ETK_HAS_NATIVE_MQUEUE
// #    define _ETK_HAS_NATIVE_TIMER
#elif defined(_ETK_HAS_THREAD_API_THREADX)
#    define _ETK_HAS_NATIVE_MUTEX
#    define _ETK_HAS_NATIVE_SEMAPHORE
// #   define _ETK_HAS_NATIVE_CONDVAR
#    define _ETK_HAS_NATIVE_EVTFLG
#    define _ETK_HAS_NATIVE_TIMER
#    define _ETK_HAS_NATIVE_MQUEUE
#    define _ETK_HAS_NATIVE_TIMER
#endif

#define _ETK_THREAD_FUNC_MAX_SIZE 64

#endif // __LIBEXPP___CONFIG_H_