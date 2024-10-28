#ifndef _ETK___THREAD_SUPPORT_H_
#define _ETK___THREAD_SUPPORT_H_

#include "etk/__config.h"

/*
The library provides support for multiple threading implementations.
This is mostly stolen from libcxx with a few modifications.
The following functionality must be provided by any implementation:


_ETK_BEGIN_NAMESPACE_ETK

//
// mutex
//
using __etk_mutex_t = ...;
#define _ETK_MUTEX_INITIALIZER ...

using __etk_recursive_mutex_t = ...;

int __etk_recursive_mutex_init(__etk_recursive_mutex_t*);
_ETK_NO_THREAD_SAFETY_ANALYSIS int
__etk_recursive_mutex_lock(__etk_recursive_mutex_t*);
_ETK_NO_THREAD_SAFETY_ANALYSIS bool
__etk_recursive_mutex_trylock(__etk_recursive_mutex_t*);
_ETK_NO_THREAD_SAFETY_ANALYSIS int
__etk_recursive_mutex_unlock(__etk_recursive_mutex_t*); int
__etk_recursive_mutex_destroy(__etk_recursive_mutex_t*);

_ETK_NO_THREAD_SAFETY_ANALYSIS int __etk_mutex_lock(__etk_mutex_t*);
_ETK_NO_THREAD_SAFETY_ANALYSIS bool __etk_mutex_trylock(__etk_mutex_t*);
_ETK_NO_THREAD_SAFETY_ANALYSIS int __etk_mutex_unlock(__etk_mutex_t*);
int __etk_mutex_destroy(__etk_mutex_t*);

//
// Condition Variable
//
using __etk_condvar_t = ...;
#define _ETK_CONDVAR_INITIALIZER ...

int __etk_condvar_signal(__etk_condvar_t*);
int __etk_condvar_broadcast(__etk_condvar_t*);
_ETK_NO_THREAD_SAFETY_ANALYSIS int __etk_condvar_wait(__etk_condvar_t*,
__etk_mutex_t*); _ETK_NO_THREAD_SAFETY_ANALYSIS int
__etk_condvar_timedwait(__etk_condvar_t*, __etk_mutex_t*, __etk_timespec_t*);
int __etk_condvar_destroy(__etk_condvar_t*);

//
// Thread ID
//
using __etk_thread_id = ...;

bool __etk_thread_id_equal(__etk_thread_id, __etk_thread_id);
bool __etk_thread_id_less(__etk_thread_id, __etk_thread_id);

//
// Thread
//
#define _ETK_NULL_THREAD ...
using __etk_thread_t = ...;

bool __etk_thread_isnull(const __etk_thread_t*);
int __etk_thread_create(__etk_thread_t*, const char *name,
                        void* (*__func)(void*), void* __arg, int __priority,
                        void* __stack, size_t __stack_size);
const char* __etk_thread_get_name(const __etk_thread_t*);
__etk_thread_id __etk_thread_get_current_id();
__etk_thread_id __etk_thread_get_id(const __etk_thread_t*);
int __etk_thread_join(__etk_thread_t*);
int __etk_thread_detach(__etk_thread_t*);
void __etk_thread_yield();

//
// Thread local storage
//
#define _ETK_TLS_DESTRUCTOR_CC ...
using __etk_tls_key = ...;

int __etk_tls_create(__etk_tls_key*, void (*__at_exit)(void*));
void* __etk_tls_get(__etk_tls_key);
int __etk_tls_set(__etk_tls_key, void*);

_ETK_END_NAMESPACE_ETK
*/

#if defined(_ETK_HAS_THREAD_API_PTHREAD)
#include "etk/__thread/support/pthread.h"
#else
#error "No thread support API defined"
#endif

#endif // _ETK___THREAD_SUPPORT_H_