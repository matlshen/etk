#ifndef _ETK___CONDITION_VARIABLE_SUPPORT_APPLE_H_
#define _ETK___CONDITION_VARIABLE_SUPPORT_APPLE_H_

#include "etk/__config.h"
#include "etk/__mutex/support/apple.h"

_ETK_BEGIN_NAMESPACE_ETK

//
// Condition Variable
//
typedef pthread_cond_t __etk_condvar_t;
#define _ETK_CONDVAR_INITIALIZER PTHREAD_COND_INITIALIZER

inline _ETK_API_INTERNAL int __etk_condvar_signal(__etk_condvar_t *__cv) {
    return pthread_cond_signal(__cv);
}

inline _ETK_API_INTERNAL int __etk_condvar_broadcast(__etk_condvar_t *__cv) {
    return pthread_cond_broadcast(__cv);
}

inline _ETK_API_INTERNAL int __etk_condvar_wait(__etk_condvar_t *__cv,
                                                __etk_mutex_t *__m) {
    return pthread_cond_wait(__cv, __m);
}

inline _ETK_API_INTERNAL int __etk_condvar_destroy(__etk_condvar_t *__cv) {
    return pthread_cond_destroy(__cv);
}

_ETK_END_NAMESPACE_ETK

#endif // _ETK___CONDITION_VARIABLE_SUPPORT_APPLE_H_