#ifndef __ETK_PERIODIC___PERIODIC_H__
#define __ETK_PERIODIC___PERIODIC_H__

#include "etk/__config.h"
#include "etk/functor.h"
#include <array>
#include <cstdint>

_ETK_BEGIN_NAMESPACE_ETK

class PeriodicTask {

};

template <size_t N>
class PeriodicScheduler {
    char __fbuf_[_ETK_THREAD_FUNC_MAX_SIZE * N];
public:
    template <class _Fp, class... _Args>
    void addTask(uint32_t __period_ms, _Fp &&__func, _Args &&...__args) {
        Functor<_Fp> task(std::forward<_Fp>(__func));
        __tasks_[__task_count_++] = task;
    }
private:
    std::array<PeriodicTask, N> __tasks_;
    size_t __task_count_ = 0;
};

_ETK_END_NAMESPACE_ETK

#endif // __ETK_PERIODIC___PERIODIC_H__