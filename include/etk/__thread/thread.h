#ifndef _ETK___THREAD_THERAD_H_
#define _ETK___THREAD_THERAD_H_

#include "etk/__config.h"
#include "etk/__thread/support.h"
#include "etk/assert.h"
#include <tuple>
#include <utility>

_ETK_BEGIN_NAMESPACE_ETK

enum class priority {
    idle = -3,
    low = -2,
    below_normal = -1,
    normal = 0,
    above_normal = 1,
    high = 2,
    realtime = 3,
    isr = 4,
    error = 5
};

struct thread_attributes {
    const char *__name{""};
    priority __priority{priority::normal};
    void *__stack{nullptr};
    size_t __stack_size{0};
};

class thread {
    __etk_thread_t __t_;

    // Buffer to store thread function and arguments
    char __fbuf_[_ETK_THREAD_FUNC_MAX_SIZE];

    thread(const thread &);
    thread &operator=(const thread &);

  public:
    using id = __etk_thread_id;

    /**
     * @brief Construct a new thread object
     *
     * @tparam _Fp Pointer to thread function
     * @tparam _Args Arguments to pass to thread function
     */
    template <class _Fp, class... _Args>
    thread(_Fp &&__func, _Args &&...__args) noexcept;

    /**
     * @brief Construct a new thread object
     *
     * @param __attr Thread attributes
     * @tparam _Fp Pointer to thread function
     * @tparam _Args Arguments to pass to thread function
     */
    template <class _Fp, class... _Args>
    thread(thread_attributes &__attr, _Fp &&__func, _Args &&...__args) noexcept;

    /**
     * @brief Default destructor
     */
    ~thread() noexcept = default;

    /**
     * @brief Move constructor
     */
    // thread(thread&& t) noexcept : __t_(t.__t_) {
    //     t.__t_ = _ETK_NULL_THREAD;
    // }

    bool joinable() const noexcept {
        return !__etk_thread_isnull(&__t_);
    }

    void join() {
        __etk_thread_join(&__t_);
    }

    void detach() {
        __etk_thread_detach(&__t_);
    }

    id get_id() const noexcept {
        return __etk_thread_get_id(&__t_);
    }

    const char *get_name() const noexcept {
        return __etk_thread_get_name(&__t_);
    }

  private:
    template <class _Fp, class... _Args>
    void __commonCtor_(thread_attributes &__attr, _Fp &&__func,
                       _Args &&...__args) noexcept;

    template <class _Fp, class... _Args>
    static void *__callAdapter_(void *arg) noexcept;

    // Alternative implementation for ThreadX
    // TODO: Find more elegant way to do this
    template <class _Fp, class... _Args>
    static void __callAdapter_(long unsigned int arg) noexcept;

    void __threadEntry() noexcept {
        __etk_thread_entry(&__t_);
    }

    void __threadExit() noexcept {
        __etk_thread_exit(&__t_);
    }
};

// Class function definitions
template <class _Fp, class... _Args>
thread::thread(_Fp &&__func, _Args &&...__args) noexcept {
    thread_attributes __attr;
    __commonCtor_(__attr, std::forward<_Fp>(__func),
                  std::forward<_Args>(__args)...);
}

template <class _Fp, class... _Args>
thread::thread(thread_attributes &__attr, _Fp &&__func,
               _Args &&...__args) noexcept {
    __commonCtor_(__attr, std::forward<_Fp>(__func),
                  std::forward<_Args>(__args)...);
}

// Utility function definitions
template <class _Fp, class... _Args>
void thread::__commonCtor_(thread_attributes &__attr, _Fp &&__func,
                           _Args &&...__args) noexcept {
    using __Ct = std::tuple<thread*, std::decay_t<_Fp>, std::decay_t<_Args>...>;
    STATIC_ASSERT_MSG(sizeof(__Ct) <= sizeof(__fbuf_),
                      "thread function too large");
    // __Ct *__ct = new (__fbuf_)
    //     __Ct(std::forward<_Fp>(__func), std::forward<_Args>(__args)...);
    __Ct *__ct = reinterpret_cast<__Ct *>(__fbuf_);
    *__ct = __Ct{this, std::forward<_Fp>(__func), std::forward<_Args>(__args)...};

    ASSERT_0(__etk_thread_create(&__t_, __attr.__name,
                                 &thread::__callAdapter_<_Fp, _Args...>, __ct,
                                 static_cast<int>(__attr.__priority),
                                 __attr.__stack, __attr.__stack_size));
}

template <class _Fp, class... _Args>
void *thread::__callAdapter_(void *arg) noexcept {
    using __Ct = std::tuple<thread*, _Fp, _Args...>;
    __Ct *__ct = static_cast<__Ct *>(arg);
    std::get<0>(*__ct)->__threadExit();
    std::apply(
        [](auto&&, auto &&__func, auto &&...__args) {
            __func(std::forward<decltype(__args)>(__args)...);
        },
        *__ct);
    std::get<0>(*__ct)->__threadExit();
    return nullptr;
}

template <class _Fp, class... _Args>
void thread::__callAdapter_(long unsigned int arg) noexcept {
    using __Ct = std::tuple<thread*, _Fp, _Args...>;
    __Ct *__ct = reinterpret_cast<__Ct *>(arg);
    std::get<0>(*__ct)->__threadEntry();
    std::apply(
        [](auto&&, auto &&__func, auto &&...__args) {
            __func(std::forward<decltype(__args)>(__args)...);
        },
        *__ct);
    std::get<0>(*__ct)->__threadExit();
}

_ETK_END_NAMESPACE_ETK

#endif // _ETK___THREAD_THERAD_H_