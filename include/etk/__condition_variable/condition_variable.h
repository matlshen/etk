#ifndef _ETK___CONDITION_VARIABLE_CONDITION_VARIABLE_H_
#define _ETK___CONDITION_VARIABLE_CONDITION_VARIABLE_H_

#include "etk/__condition_variable/support.h"
#include "etk/__config.h"
#include "etk/mutex.h"

_ETK_BEGIN_NAMESPACE_ETK

#if defined(_ETK_HAS_NATIVE_CONDVAR)

class condition_variable {
    __etk_condvar_t __cv_ = _ETK_CONDVAR_INITIALIZER;

  public:
    condition_variable()                          = default;
    condition_variable(const condition_variable&) = delete;

    ~condition_variable() { ASSERT_0(__etk_condvar_destroy(&__cv_)); }

    void notify_one() noexcept { ASSERT_0(__etk_condvar_signal(&__cv_)); }

    void notify_all() noexcept { ASSERT_0(__etk_condvar_broadcast(&__cv_)); }

    void wait(unique_lock<mutex>& lock) noexcept {
        ASSERT(lock.owns_lock());
        int ec = __etk_condvar_wait(&__cv_, lock.mutex()->native_handle());
        ASSERT_0(ec);
    }

    template <class Predicate>
    void wait(unique_lock<mutex>& lock, Predicate pred) {
        while (!pred()) {
            wait(lock);
        }
    }

    using native_handle_type = __etk_condvar_t*;
    native_handle_type native_handle() noexcept { return &__cv_; }
};

#else
// TODO: Implement this
STATIC_ASSERT(false, "No condition variable implementation available");
#endif

_ETK_END_NAMESPACE_ETK

#endif // _ETK___CONDITION_VARIABLE_CONDITION_VARIABLE_H_