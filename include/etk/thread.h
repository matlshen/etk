#ifndef __ETK_THREAD_H_
#define __ETK_THREAD_H_

/**
########## Thread synopsis ##########

namespace etk {

template <size_t StackSize = 1024>
class thread {
public:
    class id;

    template <class F, class ...Args>
    explicit thread(F&& f, Args&&... args) noexcept;

    template <class F, class ...Args>
    explicit thread(priority prio, F&& f, Args&&... args) noexcept;

    template <class F, class ...Args>
    explicit thread(const char *name,
                    priority prio, F&& f, Args&&... args) noexcept;

    ~thread();

    thread(const thread&) = delete;
    thread& operator=(thread&& t) noexcept;

    bool joinable() const noexcept;
    void join();
    void detach();
    id get_id() const noexcept;

    const char* get_name() const noexcept;
};

namespace this_thread {

    void yield() noexcept;

    void msleep(unsigned int __ms);

    void usleep(unsigned int __us);

}

using thread = thread<1024>;

}   // etk
 */

#include "etk/__config.h"
#include "etk/__thread/os.h"
#include "etk/__thread/this_thread.h"
#include "etk/__thread/thread.h"

#endif // __ETK_THREAD_H_