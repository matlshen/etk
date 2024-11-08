#ifndef _ETK___SEMAPHORE_SUPPORT_THREADX_H_
#define _ETK___SEMAPHORE_SUPPORT_THREADX_H_

#include "etk/__config.h"
#include "tx_api.h"

_ETK_BEGIN_NAMESPACE_ETK

typedef TX_SEMAPHORE __etk_semaphore_t;
#define __ETK_SEMAPHORE_INIT_VALUE__                                           \
    { 0 }

inline _ETK_API_INTERNAL int
__etk_semaphore_init(__etk_semaphore_t* __s, unsigned int __count) {
    return tx_semaphore_create(__s, NULL, __count);
}

inline _ETK_API_INTERNAL int __etk_semaphore_post(__etk_semaphore_t* __s) {
    return tx_semaphore_put(__s);
}

inline _ETK_API_INTERNAL int __etk_semaphore_wait(__etk_semaphore_t* __s) {
    return tx_semaphore_get(__s, TX_WAIT_FOREVER);
}

inline _ETK_API_INTERNAL bool __etk_semaphore_trywait(__etk_semaphore_t* __s) {
    return tx_semaphore_get(__s, TX_NO_WAIT) == TX_SUCCESS;
}

inline _ETK_API_INTERNAL int
__etk_semaphore_getvalue(__etk_semaphore_t* __s, int* __value) {
    return tx_semaphore_info_get(__s, NULL, (ULONG*)&__value, NULL, NULL, NULL);
}

inline _ETK_API_INTERNAL int __etk_semaphore_destroy(__etk_semaphore_t* __s) {
    return tx_semaphore_delete(__s);
}

_ETK_END_NAMESPACE_ETK

#endif // _ETK___SEMAPHORE_SUPPORT_THREADX_H_