#ifndef _ETK___MUTEX_UNIQUE_LOCK_H_
#define _ETK___MUTEX_UNIQUE_LOCK_H_

#include "etk/__config.h"
#include "etk/__mutex/mutex.h"

_ETK_BEGIN_NAMESPACE_ETK

constexpr int DEFER_LOCK = 0;
constexpr int TRY_TO_LOCK = 1;

class unique_lock {
  private:
    etk::mutex *__m_;
    bool __owns_;

  public:
    [[__nodiscard__]] explicit unique_lock(mutex &__m);
    [[__nodiscard__]] unique_lock(mutex &__m, int type);

    ~unique_lock();

    // Do not allow copy
    unique_lock(const unique_lock &) = delete;
    unique_lock &operator=(const unique_lock &) = delete;

    // Allow move
    unique_lock(unique_lock &&);
    unique_lock &operator=(unique_lock &&);

    void lock();
    bool try_lock();
    void unlock();

    mutex *release() noexcept;

    bool owns_lock() const noexcept;
    mutex *mutex() const noexcept;
};

_ETK_END_NAMESPACE_ETK

#endif // _ETK___MUTEX_UNIQUE_LOCK_H_