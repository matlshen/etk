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
void msleep(unsigned int __ms);

void usleep(unsigned int __us);

} // namespace this_thread

_ETK_END_NAMESPACE_ETK

#endif // _ETK___THREAD_THIS_THREAD_H_