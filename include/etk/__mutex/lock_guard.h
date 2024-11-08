#ifndef _ETK___MUTEX_LOCK_GUARD_H_
#define _ETK___MUTEX_LOCK_GUARD_H_

#include "etk/__config.h"

_ETK_BEGIN_NAMESPACE_ETK

template <class _Mutex>
class lock_guard {
  public:
    typedef _Mutex mutex_type;

  private:
    mutex_type* __m_;

  public:
    lock_guard(mutex_type& __m) : __m_(&__m) { __m_->lock(); }

    ~lock_guard() { __m_->unlock(); }

    lock_guard(const lock_guard&)            = delete;
    lock_guard& operator=(const lock_guard&) = delete;

    lock_guard(lock_guard&&)            = default;
    lock_guard& operator=(lock_guard&&) = default;

    mutex_type* mutex() const noexcept { return __m_; }
};

_ETK_END_NAMESPACE_ETK

#endif // _ETK___MUTEX_LOCK_GUARD_H_