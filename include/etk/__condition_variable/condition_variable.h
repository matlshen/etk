#ifndef _ETK___CONDITION_VARIABLE_CONDITION_VARIABLE_H_
#define _ETK___CONDITION_VARIABLE_CONDITION_VARIABLE_H_

#include "etk/__config.h"
#include "etk/__thread/support.h"
#include "etk/mutex.h"

_ETK_BEGIN_NAMESPACE_ETK

class condition_variable {
    __etk_condvar_t __cv_ = _ETK_CONDVAR_INITIALIZER;

  public:
    condition_variable() noexcept = default;
    ~condition_variable();

    condition_variable(const condition_variable &) = delete;
    condition_variable &operator=(const condition_variable &) = delete;

    void notify_one() noexcept;
    void notify_all() noexcept;

    void wait(unique_lock<mutex> &__lk) noexcept;
    template <class _Predicate>
    void wait(unique_lock<mutex> &__lk, _Predicate __pred);
};

condition_variable::~condition_variable() { __etk_condvar_destroy(&__cv_); }

template <class _Predicate>
void condition_variable::wait(unique_lock<mutex> &__lk, _Predicate __pred) {
    while (!__pred()) {
        wait(__lk);
    }
}

void condition_variable::notify_one() noexcept { __etk_condvar_signal(&__cv_); }

void condition_variable::notify_all() noexcept {
    __etk_condvar_broadcast(&__cv_);
}

void condition_variable::wait(unique_lock<mutex> &__lk) noexcept {
    ASSERT(__lk.owns_lock());
    int ec = __etk_condvar_wait(&__cv_, __lk.mutex()->native_handle());
    ASSERT_0(ec);
}

_ETK_END_NAMESPACE_ETK

#endif // _ETK___CONDITION_VARIABLE_CONDITION_VARIABLE_H_