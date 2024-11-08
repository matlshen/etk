#ifndef _ETK___THREAD_PERIODIC_H_
#define _ETK___THREAD_PERIODIC_H_

#include "etk/__condition_variable/condition_variable.h"
#include "etk/__config.h"
#include "etk/__mutex/mutex.h"
#include "etk/__thread/os.h"
#include "etk/__thread/this_thread.h"
#include "etk/__thread/thread.h"
#include "etk/functor.h"
#include "etl/priority_queue.h"
#include <iostream>

_ETK_BEGIN_NAMESPACE_ETK

// Create a tuple that can be used for comparison for priority_queue
struct __task_t {
    functor<void()> f;
    unsigned int period;
    unsigned int sched_time;
    bool run_once;

    // TODO: Make this an argument for q instead of this
    bool operator<(const __task_t& rhs) const {
        return sched_time > rhs.sched_time;
    }
    bool operator>(const __task_t& rhs) const {
        return sched_time < rhs.sched_time;
    }
};

using periodic_task_handle = __task_t*;

template <size_t N>
class periodic_svc {
  public:
    periodic_svc();
    // periodic_svc(thread_attributes &attr);
    periodic_task_handle
    add_task(const functor<void()>& f, unsigned int period);
    periodic_task_handle add_task(void (*f)(), unsigned int period);
    void join();
    void start();
    void stop();

  private:
    void __svc(void* arg);
    bool stop_;
    etl::priority_queue<__task_t, N> __q_;
    thread __t_;
    mutex __m_;
    condition_variable __cv_;
};

template <size_t N>
periodic_svc<N>::periodic_svc()
    : stop_(false), __t_([this]() { this->__svc(nullptr); }) {}

template <size_t N>
periodic_task_handle
periodic_svc<N>::add_task(const functor<void()>& f, unsigned int period) {
    unique_lock __lk(__m_);
    __task_t task = {f, period, 0, false};
    __q_.push(task);
    __cv_.notify_one();
    return &__q_.top(); // TODO: Make sure this will not choose incorrect
}

template <size_t N>
periodic_task_handle
periodic_svc<N>::add_task(void (*f)(), unsigned int period) {
    functor<void()> fc(*f);
    return add_task(fc, period);
}

template <size_t N>
void periodic_svc<N>::join() {
    __t_.join();
}

template <size_t N>
void periodic_svc<N>::start() {
    unique_lock __lk(__m_);
    stop_ = false;
    __cv_.notify_one();
}

template <size_t N>
void periodic_svc<N>::stop() {
    stop_ = true;
}

template <size_t N>
void periodic_svc<N>::__svc(void* arg) {
    (void)arg;
    while (!stop_) {
        unique_lock __lk(__m_);
        __cv_.wait(__lk, [this]() { return !(this->__q_.empty()); });

        __task_t task = __q_.top();
        __q_.pop();
        __lk.unlock();

        if (task.sched_time > etk::os::time_get()) {
            etk::this_thread::msleep(task.sched_time - etk::os::time_get());
        }

        // If this was the first time this task was run
        if (task.sched_time == 0) {
            task.sched_time = etk::os::time_get() + task.period;
        } else {
            task.sched_time += task.period;
        }
        task.f();

        __lk.lock();
        if (!task.run_once) {
            __q_.push(task);
        }
    }
}

_ETK_END_NAMESPACE_ETK

#endif // _ETK___THREAD_PERIODIC_H_