#ifndef _ETK___THREAD_THIS_THREAD_H_
#define _ETK___THREAD_THIS_THREAD_H_

#include "etk/__config.h"
#include "etk/__thread/support.h"
#include <chrono>

_ETK_BEGIN_NAMESPACE_ETK

namespace this_thread {

/**
 * Standard library functions
 */
// void sleep_for(const std::chrono::nanoseconds &__ns);

inline void yield() noexcept { __etk_thread_yield(); }

/**
 * Additional functions
 */
inline void msleep(unsigned int __ms) { __etk_thread_msleep(__ms); }

inline void usleep(unsigned int __us) { __etk_thread_msleep(__us / 1000); }

} // namespace this_thread

/**
 * Additional OS utility functions
 */
namespace os {

inline void time_start() { __etk_thread_time_start(); }

inline unsigned int time_get() { return __etk_thread_time_get(); }

} // namespace os

_ETK_END_NAMESPACE_ETK

#endif // _ETK___THREAD_THIS_THREAD_H_