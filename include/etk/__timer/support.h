#ifndef _ETK___TIMER_SUPPORT_H_
#define _ETK___TIMER_SUPPORT_H_

#include "etk/__config.h"

#if defined(_ETK_HAS_THREAD_API_PTHREAD)
// TODO
#elif defined(_ETK_HAS_THREAD_API_APPLE)
#else
#    error "No timer support"
#endif

#endif // _ETK___TIMER_SUPPORT_H_