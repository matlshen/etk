#ifndef _ETK___CONDITION_VARIABLE_SUPPORT_H_
#define _ETK___CONDITION_VARIABLE_SUPPORT_H_

/*
The library provides support for multiple condition variable implementations.
The following functionality must be provided by any implementation:

_ETK_BEGIN_NAMESPACE_ETK

//
// Condition Variable
//
using etk_condvar_t = ...;
#define _ETK_SEMAPHORE_INITIALIZER ...

int __etk_condvar_signal(__etk_condvar_t*);
int __etk_condvar_broadcast(__etk_condvar_t*);
int __etk_condvar_wait(__etk_condvar_t*, __etk_mutex_t*);
int __etk_condvar_destroy(__etk_condvar_t*);

_ETK_END_NAMESPACE_ETK
*/

#include "etk/__config.h"

#if defined(_ETK_HAS_THREAD_API_APPLE)
#include "etk/__condition_variable/support/apple.h"
#endif

#endif // _ETK___CONDITION_VARIABLE_SUPPORT_H_