#include "etk/thread.h"

_ETK_BEGIN_NAMESPACE_ETK

const char *Thread::getName() const { return __etk_thread_get_name(&__t_); }

bool Thread::joinable() const { return !__etk_thread_isnull(&__t_); }

void Thread::join() { __etk_thread_join(&__t_); }

void Thread::detach() { __etk_thread_detach(&__t_); }

Thread::Id Thread::getId() const { return __etk_thread_get_id(&__t_); }

_ETK_END_NAMESPACE_ETK