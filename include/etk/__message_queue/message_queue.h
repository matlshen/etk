#ifndef ETK_MESSAGE_QUEUE_H
#define ETK_MESSAGE_QUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include <etl/queue.h>

namespace etk {

template <typename T, size_t N>
class MessageQueue {
public:
    MessageQueue() = default;
    ~MessageQueue() = default;

    // Disable copy constructor and assignment operator
    MessageQueue(const MessageQueue&) = delete;
    MessageQueue& operator=(const MessageQueue&) = delete;

    // Enqueue a message
    void enqueue(const T& message) {
        std::lock_guard<std::mutex> lock(mutex_);
        queue_.push(message);
        if (queue_.size() == 1)
            cond_var_.notify_one();
    }

    // Dequeue a message
    T dequeue() {
        std::unique_lock<std::mutex> lock(mutex_);
        cond_var_.wait(lock, [this] { return !queue_.empty(); });
        T message = queue_.front();
        queue_.pop();
        return message;
    }

    // Check if the queue is empty
    bool empty() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.empty();
    }

private:
    mutable std::mutex mutex_;
    std::condition_variable cond_var_;
    etl::queue<T, N> queue_;
};

} // namespace etk

#endif // ETK_MESSAGE_QUEUE_H