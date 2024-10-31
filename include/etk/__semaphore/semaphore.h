#ifndef _ETK___SEMAPHORE_SEMAPHORE_H_
#define _ETK___SEMAPHORE_SEMAPHORE_H_

#include "etk/__condition_variable/condition_variable.h"
#include "etk/__config.h"
#include "etk/__mutex/mutex.h"

_ETK_BEGIN_NAMESPACE_ETK

class semaphore {
  private:
#if defined(_ETK_HAS_NATIVE_SEMAPHORE)
    __etk_semaphore_t __sem_ = _ETK_SEMAPHORE_INITIALIZER;
#endif
  public:
    semaphore(unsigned int initial) noexcept;
    ~semaphore() noexcept = default;

    // Do not allow copying
    semaphore(const semaphore &) = delete;
    semaphore &operator=(const semaphore &) = delete;

    void wait();
    bool try_wait();
    void signal();

    unsigned int count();

  private:
#if !defined(_ETK_HAS_NATIVE_SEMAPHORE)
    unsigned int __count_;
    condition_variable cond_var_;
    mutex mutex_;
#endif
};

#if defined(_ETK_HAS_NATIVE_SEMAPHORE)
#include "etk/__semaphore/native_semaphore_impl.cpp"
#else
#include "etk/__semaphore/semaphore_impl.cpp"
#endif

_ETK_END_NAMESPACE_ETK

#endif // __ETK___SEMAPHORE_SEMAPHORE_H_