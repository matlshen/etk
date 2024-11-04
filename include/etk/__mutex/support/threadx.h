#ifndef _ETK___MUTEX_SUPPORT_THREADX_H_
#define _ETK___MUTEX_SUPPORT_THREADX_H_

#include "../../rtos/threadx/tx_api.h"
#include "etk/__config.h"

_ETK_BEGIN_NAMESPACE_ETK

//
// mutex
//
typedef TX_MUTEX __etk_mutex_t; // ThreadX mutexes are recursive
#define _ETK_MUTEX_INITIALIZER                                                 \
    { 0 }

inline _ETK_API_INTERNAL int __etk_mutex_init(__etk_mutex_t *__m) {
    // TODO: create non-recursive mutex
    return tx_mutex_create(__m, (char *)"", TX_INHERIT);
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

typedef TX_MUTEX __etk_recursive_mutex_t;
#define _ETK_RECURSIVE_MUTEX_INITIALIZER                                       \
    { 0 }

inline _ETK_API_INTERNAL int
__etk_recursive_mutex_init(__etk_recursive_mutex_t *__m) {
    return tx_mutex_create(__m, (char *)"", TX_INHERIT);
}

inline _ETK_API_INTERNAL int
__etk_recursive_mutex_lock(__etk_recursive_mutex_t *__m) {
    return tx_mutex_get(__m, TX_WAIT_FOREVER);
}

inline _ETK_API_INTERNAL bool
__etk_recursive_mutex_trylock(__etk_recursive_mutex_t *__m) {
    return tx_mutex_get(__m, TX_NO_WAIT) == TX_SUCCESS;
}

inline _ETK_API_INTERNAL int
__etk_recursive_mutex_unlock(__etk_recursive_mutex_t *__m) {
    return tx_mutex_put(__m);
}

inline _ETK_API_INTERNAL int
__etk_recursive_mutex_destroy(__etk_recursive_mutex_t *__m) {
    return tx_mutex_delete(__m);
}

_ETK_END_NAMESPACE_ETK

#endif // _ETK___MUTEX_SUPPORT_THREADX_H_