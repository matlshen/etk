#ifndef _ETK___ACTIVE_OBJECT_ACTIVE_OBJECT_H_
#define _ETK___ACTIVE_OBJECT_ACTIVE_OBJECT_H_

#include "etk/__config.h"
#include "etk/__message_queue/message_queue.h"
#include "etk/__thread/thread.h"

_ETK_BEGIN_NAMESPACE_ETK

template <size_t StackSize, typename TQueueType, size_t TQueueSize = 1> class active_object {
  private:
    thread<StackSize> __thread_;
    message_queue<TQueueType, TQueueSize> __queue_;

  public:
    active_object() : __thread_(active_object::static_thread_entry, this) {}

    active_object(priority prio) noexcept
        : __thread_(prio, active_object::static_thread_entry, this) {}

    active_object(const char *name, priority prio) noexcept
        : __thread_(name, prio, active_object::static_thread_entry, this) {}

    active_object &operator=(const active_object &) = delete;

    ~active_object() = default;

    void send(const TQueueType &message) { __queue_.send(message); }

    bool try_send(const TQueueType &message) {
        return __queue_.try_send(message);
    }

    void join() { __thread_.join(); }

    virtual bool process(TQueueType &msg) = 0;

  private:
    static void static_thread_entry(void *arg) {
        return static_cast<active_object *>(arg)->thread_entry();
    }

    void thread_entry() {
        while (1) {
            TQueueType msg = __queue_.receive();
            if (!process(msg)) {
                break;
            }
        }
    }
};

_ETK_END_NAMESPACE_ETK

#endif // _ETK___ACTIVE_OBJECT_ACTIVE_OBJECT_H_