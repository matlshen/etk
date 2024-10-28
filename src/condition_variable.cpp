#include "etk/condition_variable.h"

_ETK_BEGIN_NAMESPACE_ETK

condition_variable::~condition_variable() { __etk_condvar_destroy(&__cv_); }

void condition_variable::notify_one() noexcept { __etk_condvar_signal(&__cv_); }

void condition_variable::notify_all() noexcept {
    __etk_condvar_broadcast(&__cv_);
}

void condition_variable::wait(unique_lock &__lk) noexcept {
    ASSERT(__lk.owns_lock());
    int ec = __etk_condvar_wait(&__cv_, __lk.mutex()->native_handle());
    ASSERT_0(ec);
}

_ETK_END_NAMESPACE_ETK