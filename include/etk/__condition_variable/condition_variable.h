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

    void wait(unique_lock &__lk) noexcept;
    template <class _Predicate> void wait(unique_lock &__lk, _Predicate __pred);
};

template <class _Predicate>
void condition_variable::wait(unique_lock &__lk, _Predicate __pred) {
    while (!__pred()) {
        wait(__lk);
    }
}

_ETK_END_NAMESPACE_ETK

#endif // _ETK___CONDITION_VARIABLE_CONDITION_VARIABLE_H_