#ifndef _ETK_FUNCTOR_H_
#define _ETK_FUNCTOR_H_

#include "etk/__config.h"
#include <iostream>
#include <utility>

_ETK_BEGIN_NAMESPCE_ETK

#define FP_TYPE(__f) decltype(&__f)

template <class _Fp> class Functor {
    using _Callable = std::decay_t<_Fp>;
    _Callable __c_;

  public:
    Functor(_Fp &&__f) : __c_(std::forward<_Fp>(__f)) {}

    template <class... _Args> void operator()(_Args &&...__args) {
        __c_(std::forward<_Args>(__args)...);
    }
};

_ETK_END_NAMESPCE_ETK

#endif /* _ETK_FUNCTOR_H_ */