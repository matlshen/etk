#include "etk/thread.h"

_ETK_BEGIN_NAMESPACE_ETK

const char *thread::get_name() const noexcept {
    return __etk_thread_get_name(&__t_);
}

bool thread::joinable() const noexcept { return !__etk_thread_isnull(&__t_); }

void thread::join() { __etk_thread_join(&__t_); }

void thread::detach() { __etk_thread_detach(&__t_); }

thread::id thread::get_id() const noexcept {
    return __etk_thread_get_id(&__t_);
}

namespace this_thread {

void msleep(unsigned int __ms) { __etk_thread_msleep(__ms); }

void usleep(unsigned int __us) { __etk_thread_msleep(__us / 1000); }

} // namespace this_thread

namespace os {

void time_start() { __etk_thread_time_start(); }

unsigned int time_get() { return __etk_thread_time_get(); }

} // namespace os

_ETK_END_NAMESPACE_ETK