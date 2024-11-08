#ifndef _ETK___MUTEX_SUPPORT_PTHREAD_H_
#define _ETK___MUTEX_SUPPORT_PTHREAD_H_

#include <pthread.h>

_ETK_BEGIN_NAMESPACE_ETK

//
// mutex
//
typedef pthread_mutex_t __etk_mutex_t;
#define _ETK_MUTEX_INITIALIZER PTHREAD_MUTEX_INITIALIZER

inline _ETK_API_INTERNAL int __etk_mutex_init(__etk_mutex_t* __m) {
    pthread_mutexattr_t __attr;
    int __ec = pthread_mutexattr_init(&__attr);
    if (__ec)
        return __ec;
    __ec = pthread_mutexattr_settype(&__attr, PTHREAD_MUTEX_NORMAL);
    if (__ec) {
        pthread_mutexattr_destroy(&__attr);
        return __ec;
    }
    __ec = pthread_mutex_init(__m, &__attr);
    if (__ec) {
        pthread_mutexattr_destroy(&__attr);
        return __ec;
    }
    __ec = pthread_mutexattr_destroy(&__attr);
    if (__ec) {
        pthread_mutex_destroy(__m);
        return __ec;
    }
    return 0;
}

inline _ETK_API_INTERNAL int __etk_mutex_lock(__etk_mutex_t* __m) {
    return pthread_mutex_lock(__m);
}

inline _ETK_API_INTERNAL bool __etk_mutex_trylock(__etk_mutex_t* __m) {
    return pthread_mutex_trylock(__m) == 0;
}

inline _ETK_API_INTERNAL int __etk_mutex_unlock(__etk_mutex_t* __m) {
    return pthread_mutex_unlock(__m);
}

inline _ETK_API_INTERNAL int __etk_mutex_destroy(__etk_mutex_t* __m) {
    return pthread_mutex_destroy(__m);
}

typedef pthread_mutex_t __etk_recursive_mutex_t;
#define _ETK_RECURSIVE_MUTEX_INITIALIZER PTHREAD_MUTEX_INITIALIZER

inline _ETK_API_INTERNAL int
__etk_recursive_mutex_init(__etk_recursive_mutex_t* __m) {
    pthread_mutexattr_t __attr;
    int __ec = pthread_mutexattr_init(&__attr);
    if (__ec)
        return __ec;
    __ec = pthread_mutexattr_settype(&__attr, PTHREAD_MUTEX_RECURSIVE);
    if (__ec) {
        pthread_mutexattr_destroy(&__attr);
        return __ec;
    }
    __ec = pthread_mutex_init(__m, &__attr);
    if (__ec) {
        pthread_mutexattr_destroy(&__attr);
        return __ec;
    }
    __ec = pthread_mutexattr_destroy(&__attr);
    if (__ec) {
        pthread_mutex_destroy(__m);
        return __ec;
    }
    return 0;
}

inline _ETK_API_INTERNAL int
__etk_recursive_mutex_lock(__etk_recursive_mutex_t* __m) {
    return pthread_mutex_lock(__m);
}

inline _ETK_API_INTERNAL bool
__etk_recursive_mutex_trylock(__etk_recursive_mutex_t* __m) {
    return pthread_mutex_trylock(__m) == 0;
}

inline _ETK_API_INTERNAL int
__etk_recursive_mutex_unlock(__etk_recursive_mutex_t* __m) {
    return pthread_mutex_unlock(__m);
}

inline _ETK_API_INTERNAL int
__etk_recursive_mutex_destroy(__etk_recursive_mutex_t* __m) {
    return pthread_mutex_destroy(__m);
}

_ETK_END_NAMESPACE_ETK

#endif // _ETK___MUTEX_SUPPORT_PTHREAD_H_