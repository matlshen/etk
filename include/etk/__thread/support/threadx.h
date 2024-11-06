#ifndef _ETK___THREAD_SUPPORT_THREADX_H_
#define _ETK___THREAD_SUPPORT_THREADX_H_

#include "etk/__config.h"
#include "../rtos/threadx/tx_api.h"

_ETK_BEGIN_NAMESPACE_ETK

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
// thread
//
#define _ETK_NULL_THREAD                                                       \
    { 0 }
struct tx_thread_t {
    TX_THREAD __t;
    TX_MUTEX __m;
};
typedef tx_thread_t __etk_thread_t;

bool __etk_thread_isnull(const __etk_thread_t *__t) {
    return __t->__t.tx_thread_id == 0;
}

inline _ETK_API_INTERNAL int
__etk_thread_create(__etk_thread_t *__t, const char *__name,
                    void (*__func)(long unsigned int), void *__arg,
                    int __priority, void *__stack, size_t __stack_size) {
    tx_mutex_create(&__t->__m, (char *)"", TX_NO_INHERIT);
    return tx_thread_create(&__t->__t, (char *)__name, __func, (ULONG)__arg,
                            __stack, __stack_size, __priority, __priority,
                            TX_NO_TIME_SLICE, TX_AUTO_START);
}

inline _ETK_API_INTERNAL const char *
__etk_thread_get_name(const __etk_thread_t *__t) {
    return __t->__t.tx_thread_name;
}

// TODO: deprecate get_current_id()

inline _ETK_API_INTERNAL __etk_thread_id
__etk_thread_get_id(const __etk_thread_t *__t) {
    (void)__t;
    return __t->__t.tx_thread_id;
}

inline _ETK_API_INTERNAL int __etk_thread_join(__etk_thread_t *__t) {
    return tx_mutex_get(&__t->__m, TX_WAIT_FOREVER);
}

inline _ETK_API_INTERNAL int __etk_thread_detach(__etk_thread_t *__t) {
    (void)__t;
    return -1; // Not implemented
}

inline _ETK_API_INTERNAL void __etk_thread_entry(__etk_thread_t *__t) {
    tx_mutex_get(&__t->__m, TX_WAIT_FOREVER);
}

inline _ETK_API_INTERNAL void __etk_thread_exit(__etk_thread_t *__t) {
    tx_mutex_put(&__t->__m);
}

//
// this_thread
//
inline _ETK_API_INTERNAL void __etk_thread_yield() { tx_thread_relinquish(); }

inline void __etk_thread_msleep(unsigned int __ms) {
    tx_thread_sleep(__ms / 10);
}

inline void __etk_thread_usleep(unsigned int __us) {
    tx_thread_sleep(__us / 10000);
}

inline void __etk_thread_time_start() {
    // Not implemented
}

inline unsigned int __etk_thread_time_get() { return (tx_time_get() * 10); }

_ETK_END_NAMESPACE_ETK

#endif // _ETK___THREAD_SUPPORT_THREADX_H_