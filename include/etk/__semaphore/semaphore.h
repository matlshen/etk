#ifndef _ETK___SEMAPHORE_SEMAPHORE_H_
#define _ETK___SEMAPHORE_SEMAPHORE_H_

#include "etk/__condition_variable/condition_variable.h"
#include "etk/__config.h"
#include "etk/__mutex/mutex.h"

_ETK_BEGIN_NAMESPACE_ETK

class counting_semaphore {
  public:
    counting_semaphore(unsigned int initial) noexcept;
    counting_semaphore(unsigned int max, unsigned int initial) noexcept;
    ~counting_semaphore() noexcept = default;

    // Do not allow copying
    counting_semaphore(const counting_semaphore &) = delete;
    counting_semaphore &operator=(const counting_semaphore &) = delete;

    void wait();
    bool try_wait();
    void signal();

    unsigned int count();

  private:
    unsigned int __count_;
    unsigned int __max_;
    condition_variable cond_var_;
    mutex mutex_;
};

class binary_semaphore : public counting_semaphore {
  public:
    binary_semaphore(unsigned int initial) noexcept
        : counting_semaphore(1, initial) {}
};

using semaphore = counting_semaphore;

_ETK_END_NAMESPACE_ETK

#endif // __ETK___SEMAPHORE_SEMAPHORE_H_