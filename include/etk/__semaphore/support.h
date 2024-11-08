#ifndef _ETK___SEMAPHORE_SUPPORT_H_
#define _ETK___SEMAPHORE_SUPPORT_H_

/*
The library provides support for multiple semaphore implementations.
The following functionality must be provided by any implementation:

_ETK_BEGIN_NAMESPACE_ETK

//
// Semaphore
//
using __etk_semaphore_t = ...;
#define _ETK_SEMAPHORE_INITIALIZER ...

int __etk_semaphore_init(__etk_semaphore_t*, unsigned int);
int __etk_semaphore_post(__etk_semaphore_t*);
int __etk_semaphore_wait(__etk_semaphore_t*);
bool __etk_semaphore_trywait(__etk_semaphore_t*);
int __etk_semaphore_getvalue(__etk_semaphore_t*, int*);
int __etk_semaphore_destroy(__etk_semaphore_t*);


_ETK_END_NAMESPACE_ETK
*/

#include "etk/__config.h"
#include <stddef.h>

#if defined(_ETK_HAS_THREAD_API_PTHREAD)
#    include <semaphore>
_ETK_BEGIN_NAMESPACE_ETK
template <size_t MaxCount>
using counting_semaphore = std::counting_semaphore<MaxCount>;
using binary_semaphore   = counting_semaphore<1>;
_ETK_END_NAMESPACE_ETK
#elif defined(_ETK_HAS_THREAD_API_APPLE)
#    define _ETK_HAS_NO_NATIVE_SEMAPHORE
#elif defined(_ETK_HAS_THREAD_API_THREADX)
#    include "etk/__semaphore/support/threadx.h"
#else
STATIC_ASSERT(false, "No semaphore implementation found");
#endif

#endif // _ETK___SEMAPHORE_SUPPORT_H_