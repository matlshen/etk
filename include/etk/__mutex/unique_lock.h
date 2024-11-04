#ifndef _ETK___MUTEX_UNIQUE_LOCK_H_
#define _ETK___MUTEX_UNIQUE_LOCK_H_

#include "etk/__config.h"
#include "etk/__mutex/mutex.h"
#include "etk/assert.h"

_ETK_BEGIN_NAMESPACE_ETK

constexpr int DEFER_LOCK = 0;
constexpr int TRY_TO_LOCK = 1;

template <class _Mutex> class unique_lock {
  public:
    typedef _Mutex mutex_type;

  private:
    mutex_type *__m_;
    bool __owns_;

  public:
    [[__nodiscard__]] explicit unique_lock(mutex_type &__m);
    [[__nodiscard__]] unique_lock(mutex_type &__m, int type);

    ~unique_lock();

    // Do not allow copy
    unique_lock(const unique_lock &) = delete;
    unique_lock &operator=(const unique_lock &) = delete;

    // Allow move TODO: Implement these
    unique_lock(unique_lock &&);
    unique_lock &operator=(unique_lock &&);

    void lock();
    bool try_lock();
    void unlock();

    mutex_type *release() noexcept;

    bool owns_lock() const noexcept;
    mutex_type *mutex() const noexcept;
};

template <class _Mutex>
[[__nodiscard__]] unique_lock<_Mutex>::unique_lock(mutex_type &__m)
    : __m_(&__m), __owns_(true) {
    __m_->lock();
}

template <class _Mutex>
[[__nodiscard__]] unique_lock<_Mutex>::unique_lock(mutex_type &__m, int type)
    : __m_(&__m) {
    if (type == TRY_TO_LOCK) {
        __owns_ = __m_->try_lock();
    } else if (type == DEFER_LOCK) {
        __m_->lock();
        __owns_ = true;
    } else {
        ASSERT_UNREACHABLE();
    }
}

template <class _Mutex> unique_lock<_Mutex>::~unique_lock() { __m_->unlock(); }

template <class _Mutex>
unique_lock<_Mutex>::unique_lock(unique_lock &&__u)
    : __m_(__u.__m_), __owns_(__u.__owns_) {
    __u.__m_ = nullptr;
    __u.__owns_ = false;
}

template <class _Mutex>
unique_lock<_Mutex> &unique_lock<_Mutex>::operator=(unique_lock &&__u) {
    if (__owns_) {
        __m_->unlock();
    }
    __m_ = __u.__m_;
    __owns_ = __u.__owns_;
    __u.__m_ = nullptr;
    __u.__owns_ = false;
    return *this;
}

template <class _Mutex> void unique_lock<_Mutex>::lock() {
    ASSERT(reinterpret_cast<uintptr_t>(__m_)); // Make sure __m_ is not null
    ASSERT(!__owns_);                          // Make sure not already locked
    __m_->lock();
    __owns_ = true;
}

template <class _Mutex> bool unique_lock<_Mutex>::try_lock() {
    ASSERT(reinterpret_cast<uintptr_t>(__m_)); // Make sure __m_ is not null
    ASSERT(!__owns_);                          // Make sure not already locked
    __owns_ = __m_->try_lock();
    return __owns_;
}

template <class _Mutex> void unique_lock<_Mutex>::unlock() {
    ASSERT(__owns_); // Make sure owned and locked
    __m_->unlock();
    __owns_ = false;
}

template <class _Mutex>
typename unique_lock<_Mutex>::mutex_type *
unique_lock<_Mutex>::release() noexcept {
    etk::mutex *__m = __m_;
    __m_ = nullptr;
    __owns_ = false;
    return __m;
}

template <class _Mutex> bool unique_lock<_Mutex>::owns_lock() const noexcept {
    return __owns_;
}

template <class _Mutex>
typename unique_lock<_Mutex>::mutex_type *
unique_lock<_Mutex>::mutex() const noexcept {
    return __m_;
}

_ETK_END_NAMESPACE_ETK

#endif // _ETK___MUTEX_UNIQUE_LOCK_H_