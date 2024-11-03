#ifndef _ETK_MESSAGE_QUEUE_H_
#define _ETK_MESSAGE_QUEUE_H_

/*
########## Message queue synopsis ##########

namespace etk {

class message_queue {
public:
    message_queue();
    message_queue &operator=(const message_queue &) = delete;
    ~message_queue();

    void send(const T &message);
    bool try_send(const T &message);
    T receive();
    bool try_receive(T *message);

    bool empty() const;
    bool full() const;
    size_t size() const;

    constexpr size_t capacity() const noexcept;
};

}   // etk
*/

#include "etk/__message_queue/message_queue.h"

#endif // _ETK_MESSAGE_QUEUE_H