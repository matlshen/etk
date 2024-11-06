#ifndef __ETK_TIMER___TIMER_H__
#define __ETK_TIMER___TIMER_H__

#include "etk/__config.h"
#include "etk/__thread/this_thread.h"
#include "etk/__thread/thread.h"
#include "etk/__mutex/mutex.h"
#include "etk/__condition_variable/condition_variable.h"
#include "etk/functor.h"
#include "etl/priority_queue.h"
#include <array>
#include <cstdint>
#include <iostream>

_ETK_BEGIN_NAMESPACE_ETK

struct TimerTask {
    typedef void (*func_t)(void *);

    func_t _func;
    void *_args;
    uint32_t _next_expiry;
    uint32_t _period;

    bool operator>(const TimerTask &rhs) const {
        return (_next_expiry - rhs._next_expiry) > (UINT32_MAX / 2);
    }

    bool operator<(const TimerTask &rhs) const {
        return (_next_expiry - rhs._next_expiry) < (UINT32_MAX / 2);
    }
};

template <size_t StackSize, size_t N> class timer {
  private:
	mutex __mutex_;
	condition_variable __cv_;
    thread<StackSize> __timer_svc_;
    etl::priority_queue<TimerTask, N> __tasks_;

  public:
    timer() : __timer_svc_(timer::thread_entry, this) {}
    timer(priority prio) noexcept
        : __timer_svc_(prio, timer::thread_entry, this) {}
    ~timer() = default;

    void add_task(void (*func)(void *), void *args, uint32_t delay,
                  uint32_t period) {
		unique_lock<mutex> lock(__mutex_);
        ASSERT(__tasks_.size() < N);
        TimerTask task = {func, args, os::time_get() + delay, period};
        __tasks_.push(task);
		__cv_.notify_one();
    }

	void join() { __timer_svc_.join(); }

	void detach() { __timer_svc_.detach(); }
	
  private:
    static void thread_entry(void *arg) {
        return static_cast<timer *>(arg)->svc();
    }

    void svc() {
        TimerTask currentTask;
        while (1) {
			unique_lock<mutex> lock(__mutex_);
			__cv_.wait(lock , [this] { return !__tasks_.empty(); });

			__tasks_.pop_into(currentTask);
			const uint32_t now = os::time_get();
			// Task expires in future
			if (currentTask._next_expiry >= now) {
				lock.unlock();
				this_thread::msleep(currentTask._next_expiry - now);
				lock.lock();
			}
			// Wrap-around
			else if (currentTask._next_expiry < currentTask._period) {
				lock.unlock();
				this_thread::msleep(UINT32_MAX - now +
									currentTask._next_expiry);
				lock.lock();
			}

			currentTask._func(currentTask._args);

			if (currentTask._period) {
				currentTask._next_expiry += currentTask._period;
				__tasks_.push(currentTask);
			}
        }
    }
};

_ETK_END_NAMESPACE_ETK

#endif // __ETK_TIMER___TIMER_H__