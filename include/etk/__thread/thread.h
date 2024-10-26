#ifndef _ETK___THREAD_THERAD_H_
#define _ETK___THREAD_THERAD_H_

#include "etk/__config.h"
#include "etk/__thread/support.h"
#include "etk/assert.h"
#include <tuple>
#include <utility>

_ETK_BEGIN_NAMESPACE_ETK

enum class Priority {
    Idle = -3,
    Low = -2,
    BelowNormal = -1,
    Normal = 0,
    AboveNormal = 1,
    High = 2,
    Realtime = 3,
    Isr = 4,
    Error = 5
};

struct ThreadAttributes {
    const char *__name{""};
    Priority __priority{Priority::Normal};
    void *__stack{nullptr};
    size_t __stack_size{0};
};

class Thread {
    __etk_thread_t __t_;
    char __fbuf_[_ETK_THREAD_FUNC_MAX_SIZE];

  public:
    using Id = __etk_thread_id;

    template <class _Fp, class... _Args>
    Thread(_Fp &&__func, _Args &&...__args) noexcept;

    template <class _Fp, class... _Args>
    Thread(ThreadAttributes &__attr, _Fp &&__func, _Args &&...__args) noexcept;

    ~Thread() noexcept = default;

    // Don't allow copying
    Thread(const Thread &) = delete;
    Thread(Thread &&) = delete;
    Thread &operator=(const Thread &) = delete;
    Thread &operator=(Thread &&) = delete;

    const char *getName() const;

    bool joinable() const;
    void join();
    void detach();
    Id getId() const;

  private:
    template <class _Fp, class... _Args>
    void __commonCtor_(ThreadAttributes &__attr, _Fp &&__func,
                       _Args &&...__args) noexcept;

    template <class _Fp, class... _Args>
    static void *__callAdapter_(void *arg) noexcept;
};

template <class _Fp, class... _Args>
void Thread::__commonCtor_(ThreadAttributes &__attr, _Fp &&__func,
                           _Args &&...__args) noexcept {
    using __Ct = std::tuple<std::decay_t<_Fp>, std::decay_t<_Args>...>;
    STATIC_ASSERT_MSG(sizeof(__Ct) <= sizeof(__fbuf_),
                      "Thread function too large");
    __Ct *__ct = new (__fbuf_)
        __Ct(std::forward<_Fp>(__func), std::forward<_Args>(__args)...);

    ASSERT_0(__etk_thread_create(&__t_, __attr.__name,
                                 &Thread::__callAdapter_<_Fp, _Args...>, __ct,
                                 static_cast<int>(__attr.__priority),
                                 __attr.__stack, __attr.__stack_size));
}

template <class _Fp, class... _Args>
void *Thread::__callAdapter_(void *arg) noexcept {
    using __Ct = std::tuple<_Fp, _Args...>;
    __Ct *__ct = static_cast<__Ct *>(arg);
    std::apply(
        [](auto &&__func, auto &&...__args) {
            __func(std::forward<decltype(__args)>(__args)...);
        },
        *__ct);
    return nullptr;
}

template <class _Fp, class... _Args>
Thread::Thread(_Fp &&__func, _Args &&...__args) noexcept {
    ThreadAttributes __attr;
    __commonCtor_(__attr, std::forward<_Fp>(__func),
                  std::forward<_Args>(__args)...);
}

template <class _Fp, class... _Args>
Thread::Thread(ThreadAttributes &__attr, _Fp &&__func,
               _Args &&...__args) noexcept {
    __commonCtor_(__attr, std::forward<_Fp>(__func),
                  std::forward<_Args>(__args)...);
}

_ETK_END_NAMESPACE_ETK

#endif // _ETK___THREAD_THERAD_H_