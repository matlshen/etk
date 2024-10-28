#ifndef _ETK___MUTEX_MUTEX_H_
#define _ETK___MUTEX_MUTEX_H_

#include "etk/__config.h"
#include "etk/__thread/support.h"

_ETK_BEGIN_NAMESPACE_ETK

class mutex {
    __etk_mutex_t __m_ = _ETK_MUTEX_INITIALIZER;

  public:
    mutex() noexcept;
    ~mutex() noexcept;

    // Do not allow copying
    mutex(const mutex &) = delete;
    mutex &operator=(const mutex &) = delete;

    void lock();
    bool try_lock();
    void unlock();

    typedef __etk_mutex_t *native_handle_type;
    native_handle_type native_handle() noexcept;
};

_ETK_END_NAMESPACE_ETK

#endif // _ETK___MUTEX_MUTEX_H_