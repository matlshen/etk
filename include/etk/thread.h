#ifndef __ETK_THREAD_H_
#define __ETK_THREAD_H_

/**
########## Thread synopsis ##########

namespace etk {

class thread_attributes {
public:
    const char *__name{""};
    priority_e __priority{priority_e::normal};
    void *__stack{nullptr};
    size_t __stack_size{0};
};

class thread {
public:
    class id;

    template <class F, class ...Args>
    explicit thread(F&& f, Args&&... args) noexcept;

    template <class F, class ...Args>
    explicit thread(thread_attributes& attr, F&& f, Args&&... args) noexcept;

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

    thread::id get_id() noexcept;

    void yield() noexcept;

    void msleep(unsigned int __ms);

    void usleep(unsigned int __us);

}

}   // etk
 */

#include "etk/__config.h"
#include "etk/__thread/os.h"
#include "etk/__thread/this_thread.h"
#include "etk/__thread/thread.h"

#endif // __ETK_THREAD_H_