#ifndef __ETK_MUTEX_H_
#define __ETK_MUTEX_H_

/*
########## Mutex synopsis ##########

namespace etk {

class mutex {
public:
    mutex() noexcept;
    ~mutex() noexcept;

    mutex(const mutex&) = delete;
    mutex& operator=(const mutex&) = delete;

    void lock();
    bool try_lock();
    void unlock();

    typedef __etk_mutex_t* native_handle_type;
    native_handle_type native_handle() noexcept;
};

class recursive_mutex {
public:
    recursive_mutex() noexcept;
    ~recursive_mutex() noexcept;

    recursive_mutex(const recursive_mutex&) = delete;
    recursive_mutex& operator=(const recursive_mutex&) = delete;

    void lock();
    bool try_lock();
    void unlock();

    typedef __etk_recursive_mutex_t* native_handle_type;
    native_handle_type native_handle() noexcept;
};

class unique_lock {
public:
    [[__nodiscard__]] explicit unique_lock(mutex_type& m);
    [[__nodiscard__]] unique_lock(mutex_type& m, int type);

    ~unique_lock();

    unique_lock(const unique_lock&) = delete;
    unique_lock& operator=(const unique_lock&) = delete;

    // TODO: Implement these
    unique_lock(unique_lock&&);
    unique_lock& operator=(unique_lock&&);

    void lock();
    bool try_lock();
    void unlock();

    mutex_type* release() noexcept;

    bool owns_lock() const noexcept;
    mutex_type* mutex() const noexcept;
};

}  // etk

*/

#include "etk/__config.h"
#include "etk/__mutex/mutex.h"
#include "etk/__mutex/recursive_mutex.h"
#include "etk/__mutex/unique_lock.h"

#endif // __ETK_MUTEX_H_