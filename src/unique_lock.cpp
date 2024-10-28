#include "etk/mutex.h"

_ETK_BEGIN_NAMESPACE_ETK

[[__nodiscard__]] unique_lock::unique_lock(etk::mutex &__m)
    : __m_(&__m), __owns_(true) {
    __m_->lock();
}

[[__nodiscard__]] unique_lock::unique_lock(etk::mutex &__m, int type)
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

unique_lock::~unique_lock() {
    if (__owns_) {
        __m_->unlock();
    }
}

unique_lock::unique_lock(unique_lock &&__u)
    : __m_(__u.__m_), __owns_(__u.__owns_) {
    __u.__m_ = nullptr;
    __u.__owns_ = false;
}

unique_lock &unique_lock::operator=(unique_lock &&__u) {
    if (__owns_) {
        __m_->unlock();
    }
    __m_ = __u.__m_;
    __owns_ = __u.__owns_;
    __u.__m_ = nullptr;
    __u.__owns_ = false;
    return *this;
}

void unique_lock::lock() {
    ASSERT(reinterpret_cast<uintptr_t>(__m_)); // Make sure __m_ is not null
    ASSERT(!__owns_);                          // Make sure not already locked
    __m_->lock();
    __owns_ = true;
}

bool unique_lock::try_lock() {
    ASSERT(reinterpret_cast<uintptr_t>(__m_)); // Make sure __m_ is not null
    ASSERT(!__owns_);                          // Make sure not already locked
    __owns_ = __m_->try_lock();
    return __owns_;
}

void unique_lock::unlock() {
    ASSERT(__owns_); // Make sure owned and locked
    __m_->unlock();
    __owns_ = false;
}

mutex *unique_lock::release() noexcept {
    etk::mutex *__m = __m_;
    __m_ = nullptr;
    __owns_ = false;
    return __m;
}

bool unique_lock::owns_lock() const noexcept { return __owns_; }

mutex *unique_lock::mutex() const noexcept { return __m_; }

_ETK_END_NAMESPACE_ETK