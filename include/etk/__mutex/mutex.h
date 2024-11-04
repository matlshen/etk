#ifndef _ETK___MUTEX_MUTEX_H_
#define _ETK___MUTEX_MUTEX_H_

#include "etk/__config.h"
#include "etk/__mutex/support.h"
#include "etk/assert.h"

_ETK_BEGIN_NAMESPACE_ETK

class mutex {
    __etk_mutex_t __m_ = _ETK_MUTEX_INITIALIZER;

  public:
    mutex() noexcept { ASSERT_0(__etk_mutex_init(&__m_)); }

    ~mutex() noexcept { ASSERT_0(__etk_mutex_destroy(&__m_)); }

    // Do not allow copying
    mutex(const mutex &) = delete;
    mutex &operator=(const mutex &) = delete;

    void lock() { ASSERT_0(__etk_mutex_lock(&__m_)); }

    bool try_lock() { return __etk_mutex_trylock(&__m_); }

    void unlock() { ASSERT_0(__etk_mutex_unlock(&__m_)); }

    typedef __etk_mutex_t *native_handle_type;
    native_handle_type native_handle() noexcept { return &__m_; }
};

_ETK_END_NAMESPACE_ETK

#endif // _ETK___MUTEX_MUTEX_H_