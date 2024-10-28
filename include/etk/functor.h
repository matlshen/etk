#ifndef _ETK_FUNCTOR_H_
#define _ETK_FUNCTOR_H_

#include "etk/__config.h"
#include <iostream>
#include <utility>

_ETK_BEGIN_NAMESPACE_ETK

template <class _Fp> class Functor {
    using _Callable = std::decay_t<_Fp>;
    _Callable __c_;

  public:
    /**
     * @brief Construct a new Functor object.
     *
     * @tparam __f Pointer to underlying callable object.
     */
    Functor(_Fp &&__f) : __c_(std::forward<_Fp>(__f)) {}

    /**
     * @brief Call the callable
     *
     * @tparam __args arguments to pass to the callable object.
     * @return Return value of the callable object.
     */
    template <class... _Args>
    auto operator()(_Args &&...__args) -> decltype(auto) {
        return __c_(std::forward<_Args>(__args)...);
    }
};

template <class... _Args> class FunctorArgs {
    std::tuple<_Args...> __args_;

  public:
    /**
     * @brief Construct a new FunctorArgs object.
     *
     * @tparam __args Arguments to pass to the functor.
     */
    FunctorArgs(_Args &&...__args) : __args_(std::forward<_Args>(__args)...) {}

    /**
     * @brief Get the arguments.
     *
     * @return std::tuple<_Args...> of arguments.
     */
    auto getArgs() const -> std::tuple<_Args...> { return __args_; }
};

class FunctorCaller {
  public:
    /**
     * @brief Call a functor with arguments.
     *
     * @tparam __fc Functor object
     * @tparam __args FunctorArgs object
     * @return Functor return value.
     */
    template <class _Fp, class... _Args>
    static inline auto call(Functor<_Fp> &__fc,
                            const FunctorArgs<_Args...> &__args)
        -> decltype(auto) {
        return std::apply(__fc, __args.getArgs());
    }

    /**
     * @brief Call a functor with no arguments.
     *
     * @tparam __fc Functor object.
     * @return Functor return value.
     */
    template <class _Fp>
    static inline auto call(Functor<_Fp> &__fc) -> decltype(auto) {
        return __fc();
    }
};

_ETK_END_NAMESPACE_ETK

#endif /* _ETK_FUNCTOR_H_ */