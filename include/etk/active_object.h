#ifndef _ETK_ACTIVE_OBJECT_H_
#define _ETK_ACTIVE_OBJECT_H_

/**
 * Implements the active_object pattern.
 * - An active object owns a thread and message_queue
 * - The thread runs a loop that waits to receive from the message queue
 *   and executes a virtual process task when a message is received
 * - Each active_object has a single message queue
 * - External threads can send messages to the active object
 * 
########## Active object synopsis ##########

namespace etk {

template<typename TQueueType, size_t TQueueSize = 1>
class active_object {
public:
    active_object();
    active_object(const thread_attributes& attr);
    active_object &operator=(const active_object &) = delete;
    ~active_object();

    void send(const TQueueType &message);
    bool try_send(const TQueueType &message);

    void join();

    virtual bool process(TQueueType &msg) = 0;
};

}  // etk
 */

#include "etk/__active_object/active_object.h"

#endif // _ETK_ACTIVE_OBJECT_H_