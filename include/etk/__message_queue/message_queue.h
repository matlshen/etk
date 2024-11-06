#ifndef ETK_MESSAGE_QUEUE_H
#define ETK_MESSAGE_QUEUE_H

#include "etk/__condition_variable/condition_variable.h"
#include "etk/__mutex/mutex.h"
#include "etk/__mutex/unique_lock.h"
#include <array>
#include <stddef.h>

_ETK_BEGIN_NAMESPACE_ETK

#if defined(_ETK_HAS_NATIVE_MQUEUE)

template <typename T, size_t N> class message_queue {
  private:
    __etk_mqueue_t __mq_;
    uint8_t __buf_[N * sizeof(T)];

  public:
    message_queue() { ASSERT_0(__etk_mq_init(&__mq_, N, sizeof(T))); }

    message_queue &operator=(const message_queue &) = delete;

    ~message_queue() { ASSERT_0(__etk_mq_destroy(&__mq_)); }

    void send(const T &message) {
        ASSERT_0(__etk_mq_send(&__mq_, reinterpret_cast<const void *>(&message),
                               sizeof(T)));
    }

    bool try_send(const T &message) {
        return __etk_mq_try_send(
            &__mq_, reinterpret_cast<const void *>(&message), sizeof(T));
    }

    T receive() {
        T message;
        ASSERT_0(__etk_mq_receive(&__mq_, reinterpret_cast<void *>(&message),
                                  sizeof(T)));
        return message;
    }

    bool try_receive(T *message) {
        return __etk_mq_try_receive(&__mq_, reinterpret_cast<void *>(message),
                                    sizeof(T));
    }

    bool empty() const { return __etk_mq_empty(&__mq_); }

    bool full() const { return __etk_mq_size(&__mq_) == N; }

    size_t size() const { return __etk_mq_size(&__mq_); }

    constexpr size_t capacity() const noexcept { return N; }
};

#else

template <typename T, size_t N> class message_queue {
  public:
    message_queue() noexcept = default;
    message_queue &operator=(const message_queue &) = delete;
    ~message_queue() noexcept = default;

    void send(const T &message);
    bool try_send(const T &message);
    T receive();
    bool try_receive(T *message);

    bool empty() const;
    bool full() const;
    size_t size() const;

    constexpr size_t capacity() const noexcept;

  private:
    std::array<T, N> __arr_;
    size_t __head_{0};
    size_t __tail_{0};
    size_t __size_{0};
    condition_variable cond_var_;
    mutex mutex_;
};

template <typename T, size_t N>
void message_queue<T, N>::send(const T &message) {
    unique_lock lock(mutex_);
    cond_var_.wait(lock, [this]() { return !full(); });
    __arr_[__head_] = message;
    __head_ = (__head_ + 1) % N;
    __size_++;
    cond_var_.notify_one();
}

template <typename T, size_t N>
bool message_queue<T, N>::try_send(const T &message) {
    unique_lock lock(mutex_);
    if (full()) {
        return false; // Queue is full
    }

    __arr_[__head_] = message;
    __head_ = (__head_ + 1) % capacity();
    ++__size_;

    cond_var_.notify_one();
    return true;
}

template <typename T, size_t N> T message_queue<T, N>::receive() {
    unique_lock lock(mutex_);
    cond_var_.wait(lock, [this]() { return !empty(); });

    T message = __arr_[__tail_];
    __tail_ = (__tail_ + 1) % capacity();
    --__size_;

    cond_var_.notify_one();
    return message;
}

template <typename T, size_t N>
bool message_queue<T, N>::try_receive(T *message) {
    unique_lock lock(mutex_);
    if (empty()) {
        return false;
    }

    *message = __arr_[__tail_];
    __tail_ = (__tail_ + 1) % N;
    --__size_;

    cond_var_.notify_one();
    return true;
}

template <typename T, size_t N> bool message_queue<T, N>::empty() const {
    return __size_ == 0;
}

template <typename T, size_t N> bool message_queue<T, N>::full() const {
    return __size_ == N;
}

template <typename T, size_t N> size_t message_queue<T, N>::size() const {
    return __size_;
}

template <typename T, size_t N>
constexpr size_t message_queue<T, N>::capacity() const noexcept {
    return N;
}

#endif

_ETK_END_NAMESPACE_ETK

#endif // ETK_MESSAGE_QUEUE_H