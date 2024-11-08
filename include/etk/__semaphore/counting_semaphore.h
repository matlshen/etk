#ifndef _ETK___SEMAPHORE_COUNTING_SEMAPHORE_H_
#define _ETK___SEMAPHORE_COUNTING_SEMAPHORE_H_

#include "etk/__config.h"
#include "etk/assert.h"
#if !defined(_ETK_HAS_NATIVE_SEMAPHORE)
#    include "etk/__condition_variable/condition_variable.h"
#    include "etk/__mutex/mutex.h"
#else
#    include "etk/__semaphore/support.h"
#endif
#include <stddef.h>

_ETK_BEGIN_NAMESPACE_ETK

#if defined(_ETK_HAS_NATIVE_SEMAPHORE)
#    if !defined(_ETK_HAS_THREAD_API_PTHREAD)

template <size_t MaxCount>
class counting_semaphore {
  private:
    __etk_semaphore_t __sem_{_ETK_SEMAPHORE_INITIALIZER};

  public:
    explicit counting_semaphore(size_t initial) noexcept {
        ASSERT_0(__etk_semaphore_init(&__sem_, initial));
    }

    ~counting_semaphore() noexcept {
        ASSERT_0(__etk_semaphore_destroy(&__sem_));
    }

    counting_semaphore& operator=(const counting_semaphore&) = delete;

    void release(size_t update = 1) {
        for (size_t i = 0; i < update; i++) {
            ASSERT_0(__etk_semaphore_post(&__sem_));
        }
    }

    void acquire() { ASSERT_0(__etk_semaphore_wait(&__sem_)); }

    bool try_acquire() noexcept { return __etk_semaphore_trywait(&__sem_); }

    constexpr size_t max() noexcept { return MaxCount; }

    size_t count() {
        int value;
        ASSERT_0(__etk_semaphore_getvalue(&__sem_, &value));
        return value;
    }
};

#    endif // !_ETK_HAS_THREAD_API_PTHREAD

#else

template <size_t MaxCount>
class counting_semaphore {
  public:
    constexpr explicit counting_semaphore(size_t initial) noexcept
        : __count_(initial) {
        ASSERT(__count_ >= 0 && __count_ <= max());
    }
    ~counting_semaphore() noexcept = default;

    counting_semaphore& operator=(const counting_semaphore&) = delete;

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

    constexpr size_t max() noexcept { return MaxCount; }

    size_t count() {
        unique_lock lock(mutex_);
        return __count_;
    }

  private:
    unsigned int __count_;
    condition_variable cond_var_;
    mutex mutex_;
};

#endif

_ETK_END_NAMESPACE_ETK

#endif // _ETK___SEMAPHORE_COUNTING_SEMAPHORE_H_