#ifndef __ETK___MUTEX_SUPPORT_H_
#define __ETK___MUTEX_SUPPORT_H_

#include "etk/__config.h"

/*

_ETK_BEGIN_NAMESPACE_ETK

//
// mutex
//
using __etk_mutex_t = ...;
#define _ETK_MUTEX_INITIALIZER ...

int __etk_mutex_init(__etk_mutex_t*);
int __etk_mutex_lock(__etk_mutex_t*);
bool __etk_mutex_trylock(__etk_mutex_t*);
int __etk_mutex_unlock(__etk_mutex_t*);
int __etk_mutex_destroy(__etk_mutex_t*);

using __etk_recursive_mutex_t = ...;

int __etk_recursive_mutex_init(__etk_recursive_mutex_t*);
int __etk_recursive_mutex_lock(__etk_recursive_mutex_t*);
bool __etk_recursive_mutex_trylock(__etk_recursive_mutex_t*);
int __etk_recursive_mutex_unlock(__etk_recursive_mutex_t*);
int __etk_recursive_mutex_destroy(__etk_recursive_mutex_t*);

_ETK_END_NAMESPACE_ETK

*/

#if defined(_ETK_HAS_THREAD_API_PTHREAD)
#    include "etk/__mutex/support/pthread.h"
#elif defined(_ETK_HAS_THREAD_API_APPLE)
#    include "etk/__mutex/support/pthread.h"
#elif defined(_ETK_HAS_THREAD_API_THREADX)
#    include "etk/__mutex/support/threadx.h"
#else
#    error "No mutex support"
#endif

#endif // __ETK___MUTEX_SUPPORT_H_