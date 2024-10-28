#include "etk/__semaphore/semaphore.h"
#include <limits.h>

_ETK_BEGIN_NAMESPACE_ETK

counting_semaphore::counting_semaphore(unsigned int initial) noexcept
    : __count_(initial), __max_(UINT_MAX) {}

counting_semaphore::counting_semaphore(unsigned int max,
                                       unsigned int initial) noexcept
    : __count_(initial), __max_(max) {
    ASSERT(__count_ <= __max_);
}

void counting_semaphore::wait() {
    unique_lock lock(mutex_);
    cond_var_.wait(lock, [this]() { return __count_ > 0; });
    __count_--;
}

bool counting_semaphore::try_wait() {
    unique_lock lock(mutex_);
    if (__count_ == 0) {
        return false;
    }
    __count_--;
    return true;
}

void counting_semaphore::signal() {
    unique_lock lock(mutex_);
    if (__count_ == __max_) {
        return;
    }
    __count_++;
    cond_var_.notify_one();
}

unsigned int counting_semaphore::count() {
    unique_lock lock(mutex_);
    return __count_;
}

_ETK_END_NAMESPACE_ETK