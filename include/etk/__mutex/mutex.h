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

#if defined(_ETK_HAS_NATIVE_MUTEX)

mutex::mutex() noexcept { ASSERT_0(__etk_mutex_init(&__m_)); }

mutex::~mutex() noexcept { ASSERT_0(__etk_mutex_destroy(&__m_)); }

void mutex::lock() { ASSERT_0(__etk_mutex_lock(&__m_)); }

bool mutex::try_lock() { return __etk_mutex_trylock(&__m_); }

void mutex::unlock() { ASSERT_0(__etk_mutex_unlock(&__m_)); }

mutex::native_handle_type mutex::native_handle() noexcept { return &__m_; }

#else

// Not supported

#endif

_ETK_END_NAMESPACE_ETK

#endif // _ETK___MUTEX_MUTEX_H_