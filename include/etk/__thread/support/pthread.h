#ifndef _ETK___THREAD_SUPPORT_PTHREAD_H_
#define _ETK___THREAD_SUPPORT_PTHREAD_H_

#include "etk/__config.h"
#include "etk/assert.h"
#include <pthread.h>
#include <sched.h>
#include <time.h>
#include <unistd.h>

#include "etk/__mutex/support/pthread.h"
#include "etk/assert.h"

_ETK_BEGIN_NAMESPACE_ETK

//
// Thread ID
//
typedef pthread_t __etk_thread_id;

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
// Thread
//
#define _ETK_NULL_THREAD ((__etk_thread_t){{}, ""})
struct __etk_thread_t {
    pthread_t __t_;
    const char* __name_;
};

inline _ETK_API_INTERNAL __etk_thread_id
__etk_thread_get_id(const __etk_thread_t* __t) {
    return __t->__t_;
}

inline _ETK_API_INTERNAL bool __etk_thread_isnull(const __etk_thread_t* __t) {
    return __etk_thread_get_id(__t) == 0;
}

inline _ETK_API_INTERNAL int __etk_thread_create(
    __etk_thread_t* __t,
    const char* __name,
    void* (*__func)(void*),
    void* __arg,
    int __priority,
    void* __stack,
    size_t __stack_size) {
    // Initialize the thread attributes
    pthread_attr_t attr;
    int __ec = pthread_attr_init(&attr);
    if (__ec)
        return __ec;
    // Set thread scheduling policy to Round Robin
    __ec = pthread_attr_setschedpolicy(&attr, SCHED_RR);
    if (__ec) {
        pthread_attr_destroy(&attr);
        return __ec;
    }
    // Set thread priority
    if (__priority) {
        struct sched_param __sched_param;
        __sched_param.sched_priority = __priority;
        __ec = pthread_attr_setschedparam(&attr, &__sched_param);
        if (__ec) {
            pthread_attr_destroy(&attr);
            return __ec;
        }
    }
    // Don't use static stack for pthread
    (void)__stack;
    (void)__stack_size;
    // if (__stack && __stack_size) {
    //     __ec = pthread_attr_setstack(&attr, __stack, __stack_size);
    //     if (__ec) {
    //         pthread_attr_destroy(&attr);
    //         return __ec;
    //     }
    // }
    // Create the thread
    __ec = pthread_create(&__t->__t_, nullptr, __func, __arg);
    if (__ec) {
        pthread_attr_destroy(&attr);
        return __ec;
    }
    // Destroy the thread attributes
    __ec = pthread_attr_destroy(&attr);
    if (__ec) {
        pthread_cancel(__t->__t_);
        return __ec;
    }
    // Set the thread name
    __t->__name_ = __name;
    return 0;
}

inline _ETK_API_INTERNAL const char*
__etk_thread_get_name(const __etk_thread_t* __t) {
    return __t->__name_;
}

inline _ETK_API_INTERNAL __etk_thread_id __etk_thread_get_current_id() {
    return pthread_self();
}

inline _ETK_API_INTERNAL int __etk_thread_join(__etk_thread_t* __t) {
    return pthread_join(__t->__t_, nullptr);
}

inline _ETK_API_INTERNAL int __etk_thread_detach(__etk_thread_t* __t) {
    (void)__t;
    return 0; // TODO: Is this correct?
    // return pthread_detach(__t->__t_);
}

inline _ETK_API_INTERNAL int __etk_thread_cancel(__etk_thread_t* __t) {
    (void)__t;
    return 0; // TODO: Is this correct?
    // return pthread_cancel(__t->__t_);
}

inline _ETK_API_INTERNAL void __etk_thread_entry(__etk_thread_t* __t) {
    (void)__t;
}

inline _ETK_API_INTERNAL void __etk_thread_exit(__etk_thread_t* __t) {
    (void)__t;
}

inline _ETK_API_INTERNAL void __etk_thread_yield() { sched_yield(); }

inline _ETK_API_INTERNAL void __etk_thread_msleep(unsigned int __ms) {
    usleep(__ms * 1000);
}

static struct timespec __etk_start_time, __etk_end_time;

inline _ETK_API_INTERNAL void __etk_thread_time_start() {
    clock_gettime(CLOCK_MONOTONIC, &__etk_start_time);
}

inline _ETK_API_INTERNAL unsigned int __etk_thread_time_get() {
    clock_gettime(CLOCK_MONOTONIC, &__etk_end_time);
    long __seconds = __etk_end_time.tv_sec - __etk_start_time.tv_sec;
    long __ns      = __etk_end_time.tv_nsec - __etk_start_time.tv_nsec;
    return __seconds * 1000 + __ns / 1000000;
}

_ETK_END_NAMESPACE_ETK

#endif // _ETK___THREAD_SUPPORT_PTHREAD_H_