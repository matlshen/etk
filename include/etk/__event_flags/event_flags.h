#ifndef _ETK___EVENT_FLAG_EVENT_FLAGS_H_
#define _ETK___EVENT_FLAG_EVENT_FLAGS_H_

#if defined(_ETK_HAS_NATIVE_EVTFLG)
#    include "etk/__condition_variable/support.h"
#else
#    include "etk/__condition_variable/condition_variable.h"
#    include "etk/__config.h"
#    include "etk/__mutex/mutex.h"
#    include "etk/__mutex/unique_lock.h"
#endif
#include <cstdint>

// TODO: setting event flags unblocks all threads, is this behavior correct?

_ETK_BEGIN_NAMESPACE_ETK

#if defined(_ETK_HAS_NATIVE_EVTFLG)

class event_flags {
  private:
    __etk_event_flags_t _flags;

  public:
    enum mode {
        wait_any,
        wait_all,
    };

    explicit event_flags() { ASSERT_0(event_flags_create(&_flags)); }

    ~event_flags() { ASSERT_0(event_flags_destroy(&_flags)); }

    void set(uint32_t flags) { ASSERT_0(event_flags_set(&_flags, flags)); }

    void clear(uint32_t flags) { ASSERT_0(event_flags_clear(&_flags, flags)); }

    uint32_t wait(uint32_t flags, mode wait_mode) {
        uint32_t flags_set;
        ASSERT_0(event_flags_get(&_flags, &flags_set, wait_mode));
        return flags_set;
    }
};

#else

class event_flags {
  public:
    enum mode {
        wait_any,
        wait_all,
        wait_any_clear,
        wait_all_clear,
    };

  private:
    uint32_t _flags{0};
    mutex _mutex;
    condition_variable _cv;

  public:
    event_flags()  = default;
    ~event_flags() = default;

    void set(uint32_t flags) {
        unique_lock<mutex> lock(_mutex);
        _flags |= flags;
        _cv.notify_all();
    }

    void clear(uint32_t flags) {
        unique_lock<mutex> lock(_mutex);
        _flags &= ~flags;
    }

    /**
     * @brief Wait for any of the specified flags to be set
     */
    uint32_t wait(uint32_t flags, mode wait_mode) {
        unique_lock<mutex> lock(_mutex);
        if (wait_mode == wait_any || wait_mode == wait_any_clear) {
            _cv.wait(lock, [this, flags] { return (_flags & flags) != 0; });
        } else {
            _cv.wait(lock, [this, flags] { return (_flags & flags) == flags; });
        }
        if (wait_mode == wait_any_clear || wait_mode == wait_all_clear) {
            _flags &= ~flags;
        }
        return _flags;
    }
};

#endif

_ETK_END_NAMESPACE_ETK

#endif // _ETK___EVENT_FLAG_EVENT_FLAGS_H_