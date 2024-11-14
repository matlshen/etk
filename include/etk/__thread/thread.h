#ifndef _ETK___THREAD_THERAD_H_
#define _ETK___THREAD_THERAD_H_

#include "etk/__assert/assert.h"
#include "etk/__config.h"
#include "etk/__thread/support.h"
#include <tuple>
#include <utility>

_ETK_BEGIN_NAMESPACE_ETK

enum class priority {
    idle         = -3,
    low          = -2,
    below_normal = -1,
    normal       = 0,
    above_normal = 1,
    high         = 2,
    realtime     = 3,
    isr          = 4,
    error        = 5
};

class thread {
  private:
    __etk_thread_t __t_;

    // Buffer to store thread function and arguments
    char __fbuf_[_ETK_THREAD_FUNC_MAX_SIZE];

    // Local stack
    char* __stack_{nullptr};
    size_t __stack_size_{0};

  public:
    using id = __etk_thread_id;

    /**
     * @brief Construct a new thread object
     *
     * @tparam _Fp Pointer to thread function
     * @tparam _Args Arguments to pass to thread function
     */
    template <class _Fp,
              class... _Args,
              typename = std::enable_if_t<
                  !std::is_same_v<std::decay_t<_Fp>, const char*> &&
                  std::is_invocable_v<_Fp, _Args...>>>
    // Template is wack so compiler knows which overloaded constructor to use
    explicit thread(_Fp&& __func, _Args&&... __args) noexcept {
        __commonCtor_("",
                      priority::normal,
                      std::forward<_Fp>(__func),
                      std::forward<_Args>(__args)...);
    }

    /**
     * @brief Construct a new thread object
     *
     * @param __prio Thread priority
     * @param __stack_size Stack size
     * @tparam _Fp Pointer to thread function
     * @tparam _Args Arguments to pass to thread function
     */
    template <class _Fp, class... _Args>
    explicit thread(priority __prio,
                    size_t __stack_size,
                    _Fp&& __func,
                    _Args&&... __args) noexcept {
        if (__stack_size > 0) {
            __stack_ = reinterpret_cast<char*>(memory::malloc(__stack_size));
            // Do not allow malloc to fail
            ASSERT(__stack_ != nullptr);
            __stack_size_ = __stack_size;
        }
        __commonCtor_("",
                      __prio,
                      std::forward<_Fp>(__func),
                      std::forward<_Args>(__args)...);
    }

    /**
     * @brief Construct a new thread object
     *
     * @param __name Thread name
     * @param __prio Thread priority
     * @param __stack_size Stack size
     * @tparam _Fp Pointer to thread function
     * @tparam _Args Arguments to pass to thread function
     */
    template <class _Fp, class... _Args>
    explicit thread(const char* __name,
                    priority __prio,
                    size_t __stack_size,
                    _Fp&& __func,
                    _Args&&... __args) noexcept {
        if (__stack_size > 0) {
            __stack_ = reinterpret_cast<char*>(memory::malloc(__stack_size));
            // Do not allow malloc to fail
            ASSERT(__stack_ != nullptr);
            __stack_size_ = __stack_size;
        }
        __commonCtor_(__name,
                      __prio,
                      std::forward<_Fp>(__func),
                      std::forward<_Args>(__args)...);
    }

    /**
     * @brief Destructor cancels thread and frees memory
     */
    ~thread() noexcept {
        ASSERT(__etk_thread_cancel(&__t_) == 0);
        if (__stack_ != nullptr) {
            memory::free(__stack_);
        }
    }

    /**
     * @brief Move constructor
     */
    thread(thread&& t) noexcept
        : __t_(t.__t_), __stack_(t.__stack_), __stack_size_(t.__stack_size_) {
        t.__t_          = __etk_thread_t();
        t.__stack_      = nullptr;
        t.__stack_size_ = 0;
    }

    /**
     * @brief Check if the thread is joinable
     *
     * @return true if the thread is joinable, false otherwise
     */
    bool joinable() const noexcept { return !__etk_thread_isnull(&__t_); }

    /**
     * @brief Join the thread
     */
    void join() { __etk_thread_join(&__t_); }

    /**
     * @brief Detach from the thread
     */
    void detach() { __etk_thread_detach(&__t_); }

    /**
     * @brief Get the thread id
     *
     * @return id Thread id
     */
    id get_id() const noexcept { return __etk_thread_get_id(&__t_); }

    /**
     * @brief Get the thread name
     *
     * @return const char* Thread name
     */
    const char* get_name() const noexcept {
        return __etk_thread_get_name(&__t_);
    }

  private:
    template <class _Fp, class... _Args>
    void __commonCtor_(const char* __name,
                       priority __prio,
                       _Fp&& __func,
                       _Args&&... __args) noexcept;

    template <class _Fp, class... _Args>
    static void* __callAdapter_(void* arg) noexcept;

    // Alternative implementation for ThreadX
    // TODO: Find more elegant way to do this
    template <class _Fp, class... _Args>
    static void __callAdapter_(long unsigned int arg) noexcept;

    void __threadEntry() noexcept { __etk_thread_entry(&__t_); }

    void __threadExit() noexcept { __etk_thread_exit(&__t_); }
};

// Utility function definitions
template <class _Fp, class... _Args>
void thread::__commonCtor_(const char* __name,
                           priority __prio,
                           _Fp&& __func,
                           _Args&&... __args) noexcept {
    using __Ct = std::tuple<thread*, std::decay_t<_Fp>, std::decay_t<_Args>...>;
    STATIC_ASSERT_MSG(
        sizeof(__Ct) <= sizeof(__fbuf_), "thread function too large");
    __Ct* __ct = reinterpret_cast<__Ct*>(__fbuf_);
    *__ct =
        __Ct{this, std::forward<_Fp>(__func), std::forward<_Args>(__args)...};

    ASSERT(__etk_thread_create(
               &__t_,
               __name,
               &thread::__callAdapter_<_Fp, _Args...>,
               __ct,
               static_cast<int>(__prio),
               static_cast<void*>(__stack_),
               __stack_size_) == 0);
}

template <class _Fp, class... _Args>
void* thread::__callAdapter_(void* arg) noexcept {
    using __Ct = std::tuple<thread*, _Fp, _Args...>;
    __Ct* __ct = static_cast<__Ct*>(arg);
    std::get<0>(*__ct)->__threadExit();
    std::apply(
        [](auto&&, auto&& __func, auto&&... __args) {
            __func(std::forward<decltype(__args)>(__args)...);
        },
        *__ct);
    std::get<0>(*__ct)->__threadExit();
    return nullptr;
}

template <class _Fp, class... _Args>
void thread::__callAdapter_(long unsigned int arg) noexcept {
    using __Ct = std::tuple<thread*, _Fp, _Args...>;
    __Ct* __ct = reinterpret_cast<__Ct*>(arg);
    std::get<0>(*__ct)->__threadEntry();
    std::apply(
        [](auto&&, auto&& __func, auto&&... __args) {
            __func(std::forward<decltype(__args)>(__args)...);
        },
        *__ct);
    std::get<0>(*__ct)->__threadExit();
}

_ETK_END_NAMESPACE_ETK

#endif // _ETK___THREAD_THERAD_H_