#ifndef _ETK___MUTEX_MUTEX_H_
#define _ETK___MUTEX_MUTEX_H_

#include "etk/__config.h"
#include "etk/__thread/support.h"

_ETK_BEGIN_NAMESPACE_ETK

class Mutex {
    __etk_mutex_t __m_ = _ETK_MUTEX_INITIALIZER;

  public:
    Mutex() noexcept;
    ~Mutex() noexcept;

    // Copying not allowed
    Mutex(const Mutex &) = delete;
    Mutex &operator=(const Mutex &) = delete;

    void lock();
    bool tryLock();
    void unlock();

    // Alias for tryLock for compatibility with std locks
    inline bool try_lock() { return tryLock(); }
};

_ETK_END_NAMESPACE_ETK

#endif // _ETK___MUTEX_MUTEX_H_