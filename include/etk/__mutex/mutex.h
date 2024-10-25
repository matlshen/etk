#ifndef _ETK___MUTEX_MUTEX_H_
#define _ETK___MUTEX_MUTEX_H_

#include "etk/__config.h"
#include "etk/__thread/support.h"

_ETK_BEGIN_NAMESPCE_ETK

class Mutex {
    __etk_mutex_t __m_ = _ETK_MUTEX_INITIALIZER;

  public:
    Mutex() = default;

    // Copying not allowed
    Mutex(const Mutex &) = delete;
    Mutex &operator=(const Mutex &) = delete;

    void lock();
    bool tryLock();
    void unlock();
};

_ETK_END_NAMESPCE_ETK

#endif // _ETK___MUTEX_MUTEX_H_