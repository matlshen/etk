#ifndef _ETK_FUNCTOR_H_
#define _ETK_FUNCTOR_H_

#include "etk/__config.h"
#include <tuple>
#include <utility>

_ETK_BEGIN_NAMESPACE_ETK

template <class _Fp>
class functor {
    using _Callable = std::decay_t<_Fp>;
    _Callable __c_;
    bool __empty_;

  public:
    /**
     * @brief Construct an empty functor object.
     */
    functor() noexcept : __empty_(true){};

    /**
     * @brief Construct a new functor object.
     *
     * @tparam __f Pointer to underlying callable object.
     */
    functor(_Fp&& __f) noexcept
        : __c_(std::forward<_Fp>(__f)), __empty_(false) {}

    /**
     * @brief Call the callable
     *
     * @tparam __args arguments to pass to the callable object.
     * @return Return value of the callable object.
     */
    template <class... _Args>
    auto operator()(_Args&&... __args) -> decltype(auto) {
        if (__empty_) {
            using _ReturnType = decltype(__c_(std::forward<_Args>(__args)...));
            return _ReturnType();
        }
        return __c_(std::forward<_Args>(__args)...);
    }

    /**
     * @brief Check if the functor is empty.
     *
     * @return true if the functor is empty, false otherwise.
     */
    bool empty() const noexcept { return __empty_; }
};

template <class... _Args>
class functor_args {
    std::tuple<_Args...> __args_;

  public:
    /**
     * @brief Construct a new functor_args object.
     *
     * @tparam __args Arguments to pass to the functor.
     */
    functor_args(_Args&&... __args) : __args_(std::forward<_Args>(__args)...) {}

    /**
     * @brief Get the arguments.
     *
     * @return std::tuple<_Args...> of arguments.
     */
    auto getArgs() const -> std::tuple<_Args...> { return __args_; }
};

class functorCaller {
  public:
    /**
     * @brief Call a functor with arguments.
     *
     * @tparam __fc functor object
     * @tparam __args functor_args object
     * @return functor return value.
     */
    template <class _Fp, class... _Args>
    static inline auto
    call(functor<_Fp>& __fc,
         const functor_args<_Args...>& __args) -> decltype(auto) {
        return std::apply(__fc, __args.getArgs());
    }

    /**
     * @brief Call a functor with no arguments.
     *
     * @tparam __fc functor object.
     * @return functor return value.
     */
    template <class _Fp>
    static inline auto call(functor<_Fp>& __fc) -> decltype(auto) {
        return __fc();
    }
};

_ETK_END_NAMESPACE_ETK

#endif /* _ETK_FUNCTOR_H_ */