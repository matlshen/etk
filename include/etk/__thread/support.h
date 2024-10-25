#ifndef _ETK___THREAD_SUPPORT_H_
#define _ETK___THREAD_SUPPORT_H_

#include "etk/__config.h"

/*
The library provides support for multiple threading implementations.
This is mostly stolen from libcxx with a few modifications.
The following functionality must be provided by any implementation:


_ETK_BEGIN_NAMESPCE_ETK

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
#define _LIBCPP_TLS_DESTRUCTOR_CC ...
using __libcpp_tls_key = ...;

int __libcpp_tls_create(__libcpp_tls_key*, void (*__at_exit)(void*));
void* __libcpp_tls_get(__libcpp_tls_key);
int __libcpp_tls_set(__libcpp_tls_key, void*);

_ETK_END_NAMESPCE_ETK
*/

#if defined(_ETK_HAS_THREAD_API_PTHREAD)
#include "etk/__thread/support/pthread.h"
#else
#error "No thread support API defined"
#endif

#endif // _ETK___THREAD_SUPPORT_H_