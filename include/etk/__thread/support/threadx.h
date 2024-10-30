#ifndef _ETK___THREAD_SUPPORT_THREADX_H_
#define _ETK___THREAD_SUPPORT_THREADX_H_

#include "etk/__config.h"
#include "tx_api.h"

_ETK_BEGIN_NAMESPACE_ETK

//
// mutex
//
typedef TX_MUTEX __etk_mutex_t;
#define _ETK_MUTEX_INITIALIZER {0}

typedef TX_MUTEX __etk_recursive_mutex_t;

inline _ETK_API_INTERNAL int __etk_mutex_init(__etk_recursive_mutex_t *__m) {
    return tx_mutex_create(__m, (char*)"", TX_INHERIT);
}

inline _ETK_API_INTERNAL int __etk_recursive_mutex_lock(__etk_recursive_mutex_t *__m) {
    return tx_mutex_get(__m, TX_WAIT_FOREVER);
}

inline _ETK_API_INTERNAL bool __etk_recursive_mutex_trylock(__etk_recursive_mutex_t *__m) {
    return tx_mutex_get(__m, TX_NO_WAIT) == TX_SUCCESS;
}


inline _ETK_API_INTERNAL int __etk_recursive_mutex_unlock(__etk_recursive_mutex_t *__m) {
    return tx_mutex_put(__m);
}

inline _ETK_API_INTERNAL int __etk_recursive_mutex_destroy(__etk_recursive_mutex_t *__m) {
    return tx_mutex_delete(__m);
}

inline _ETK_API_INTERNAL int __etk_mutex_lock(__etk_mutex_t *__m) {
    return tx_mutex_get(__m, TX_WAIT_FOREVER);
}

inline _ETK_API_INTERNAL bool __etk_mutex_trylock(__etk_mutex_t *__m) {
    return tx_mutex_get(__m, TX_NO_WAIT) == TX_SUCCESS;
}

inline _ETK_API_INTERNAL int __etk_mutex_unlock(__etk_mutex_t *__m) {
    return tx_mutex_put(__m);
}

inline _ETK_API_INTERNAL int __etk_mutex_destroy(__etk_mutex_t *__m) {
    return tx_mutex_delete(__m);
}

//
// Condition Variable (TODO: not implemented)
//
typedef void* __etk_condvar_t;
#define _ETK_CONDVAR_INITIALIZER NULL

inline _ETK_API_INTERNAL int __etk_condvar_signal(__etk_condvar_t *__cv) {
    return -1;
}

inline _ETK_API_INTERNAL int __etk_condvar_broadcast(__etk_condvar_t *__cv) {
    return -1;
}

inline _ETK_API_INTERNAL _LIBCPP_NO_THREAD_SAFETY_ANALYSIS int
__etk_condvar_wait(__etk_condvar_t *__cv, __etk_mutex_t *__m) {
    return -1;
}

inline _ETK_API_INTERNAL int __etk_condvar_destroy(__etk_condvar_t *__cv) {
    return -1;
}

//
// Thread ID
//
typedef ULONG __etk_thread_id;

// Returns non-zero if the thread ids are equal, otherwise 0
inline _ETK_API_INTERNAL bool __etk_thread_id_equal(__etk_thread_id __t1,
                                                    __etk_thread_id __t2) {
    return __t1 == __t2;
}

// Returns non-zero if t1 < t2, otherwise 0
inline _ETK_API_INTERNAL bool __etk_thread_id_less(__etk_thread_id __t1,
                                                   __etk_thread_id __t2) {
    return __t1 < __t2;
}

//
// Thread
// 
#define _ETK_NULL_THREAD {0}
typedef TX_THREAD __etk_thread_t;

inline _ETK_API_INTERNAL __etk_thread_id
__etk_thread_get_id(const __etk_thread_t *__t) {
    return __t->tx_thread_id;
}

inline _ETK_API_INTERNAL int __etk_thread_create(__etk_thread_t *__t, const char *__name,
                                                 void *(*__func)(void *), void *__arg, int __priority,
                                                 void *__stack, size_t __stack_size) {
    return tx_thread_create(__t, (char*)__name, (VOID(*)(ULONG))__func, (ULONG)__arg,
                            __stack, __stack_size, __priority, __priority,
                            TX_NO_TIME_SLICE, TX_AUTO_START);
}

_ETK_END_NAMESPACE_ETK

#endif // _ETK___THREAD_SUPPORT_THREADX_H_