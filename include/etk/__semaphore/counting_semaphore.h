#ifndef _ETK___SEMAPHORE_COUNTING_SEMAPHORE_H_
#define _ETK___SEMAPHORE_COUNTING_SEMAPHORE_H_

#include "etk/__config.h"
#if !defined(_ETK_HAS_NATIVE_SEMAPHORE)
#include "etk/__condition_variable/condition_variable.h"
#include "etk/__mutex/mutex.h"
#else
#include "etk/__thread/support.h"
#endif
#include <stddef.h>

_ETK_BEGIN_NAMESPACE_ETK

#if !defined(_ETK_HAS_NATIVE_SEMAPHORE)

template <size_t MaxCount> class counting_semaphore {
  public:
    constexpr explicit counting_semaphore(size_t initial) noexcept
        : __count_(initial) {
        ASSERT(__count_ >= 0 && __count_ <= max());
    }
    ~counting_semaphore() noexcept = default;

    counting_semaphore &operator=(const counting_semaphore &) = delete;

    void release(size_t update = 1) {
        unique_lock lock(mutex_);
        for (size_t i = 0; i < update; i++) {
            if (__count_ >= max()) {
                return;
            }
            __count_++;
            cond_var_.notify_one();
        }
    }

    void acquire() {
        unique_lock lock(mutex_);
        cond_var_.wait(lock, [this]() { return __count_ > 0; });
        __count_--;
    }

    bool try_acquire() noexcept {
        unique_lock lock(mutex_);
        if (__count_ == 0) {
            return false;
        }
        __count_--;
        return true;
    }

    constexpr size_t max() noexcept {
        return MaxCount;
    }

    size_t count() {
        unique_lock lock(mutex_);
        return __count_;
    }

  private:
    unsigned int __count_;
    condition_variable cond_var_;
    mutex mutex_;
};

#else

template <size_t MaxCount> class counting_semaphore {
  private:
    __etk_semaphore_t __sem_;

  public:
    constexpr explicit counting_semaphore(size_t initial) noexcept private:
};

#endif

_ETK_END_NAMESPACE_ETK

#endif // _ETK___SEMAPHORE_COUNTING_SEMAPHORE_H_