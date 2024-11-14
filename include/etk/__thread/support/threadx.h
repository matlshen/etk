#ifndef _ETK___THREAD_SUPPORT_THREADX_H_
#define _ETK___THREAD_SUPPORT_THREADX_H_

#include "../rtos/threadx/tx_api.h"
#include "etk/__config.h"

_ETK_BEGIN_NAMESPACE_ETK

//
// Helper functions
//
constexpr unsigned int __etk_to_threadx_priority(int prio) {
    switch (prio) {
    case -3:
        return TX_MAX_PRIORITIES - 1;
    case -2:
        return TX_MAX_PRIORITIES - 2;
    case -1:
        return TX_MAX_PRIORITIES - 3;
    case 0:
        return TX_MAX_PRIORITIES / 2;
    case 1:
        return 3;
    case 2:
        return 2;
    case 3:
        return 1;
    case 4:
        return 0;
    default:
        return 0;
    }
}

//
// Thread ID
//
typedef ULONG __etk_thread_id;

// Returns non-zero if the thread ids are equal, otherwise 0
inline _ETK_API_INTERNAL bool
__etk_thread_id_equal(__etk_thread_id __t1, __etk_thread_id __t2) {
    return __t1 == __t2;
}

// Returns non-zero if t1 < t2, otherwise 0
inline _ETK_API_INTERNAL bool
__etk_thread_id_less(__etk_thread_id __t1, __etk_thread_id __t2) {
    return __t1 < __t2;
}

//
// thread
//
#define _ETK_NULL_THREAD                                                       \
    { 0 }
struct tx_thread_t {
    TX_THREAD __t;
    TX_SEMAPHORE __s;
};
typedef tx_thread_t __etk_thread_t;

bool __etk_thread_isnull(const __etk_thread_t* __t) {
    return __t->__t.tx_thread_id == 0;
}

inline _ETK_API_INTERNAL int __etk_thread_create(
    __etk_thread_t* __t,
    const char* __name,
    void (*__func)(long unsigned int),
    void* __arg,
    int __priority,
    void* __stack,
    size_t __stack_size) {
    int retval = TX_SUCCESS;
    retval = tx_semaphore_create(&__t->__s, (CHAR*)"", 0);
    if (retval != TX_SUCCESS) {
        return retval;
    }
    return tx_thread_create(
        &__t->__t,
        (CHAR*)__name,
        __func,
        (ULONG)__arg,
        __stack,
        __stack_size,
        __etk_to_threadx_priority(__priority),
        __etk_to_threadx_priority(__priority),
        TX_NO_TIME_SLICE,
        TX_AUTO_START);
}

inline _ETK_API_INTERNAL const char*
__etk_thread_get_name(const __etk_thread_t* __t) {
    return __t->__t.tx_thread_name;
}

// TODO: deprecate get_current_id()

inline _ETK_API_INTERNAL __etk_thread_id
__etk_thread_get_id(const __etk_thread_t* __t) {
    (void)__t;
    return __t->__t.tx_thread_id;
}

inline _ETK_API_INTERNAL int __etk_thread_join(__etk_thread_t* __t) {
    return tx_semaphore_get(&__t->__s, TX_WAIT_FOREVER);
}

inline _ETK_API_INTERNAL int __etk_thread_detach(__etk_thread_t* __t) {
    (void)__t;
    return -1; // Not implemented
}

inline _ETK_API_INTERNAL int __etk_thread_cancel(__etk_thread_t* __t) {
    int retval = TX_SUCCESS;
    retval = tx_semaphore_delete(&__t->__s);
    if (retval != TX_SUCCESS) {
        return retval;
    }
    retval =  tx_thread_terminate(&__t->__t);
    if (retval != TX_SUCCESS) {
        return retval;
    }
    return tx_thread_delete(&__t->__t);
}

inline _ETK_API_INTERNAL void __etk_thread_entry(__etk_thread_t* __t) {
    (void)__t;
}

inline _ETK_API_INTERNAL void __etk_thread_exit(__etk_thread_t* __t) {
    tx_semaphore_put(&__t->__s);
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