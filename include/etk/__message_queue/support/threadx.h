#ifndef _ETK___MUTEX_SUPPORT_THREADX_H_
#define _ETK___MUTEX_SUPPORT_THREADX_H_

#include "../../rtos/threadx/tx_api.h"
#include "etk/__config.h"

_ETK_BEGIN_NAMESPACE_ETK

//
// message queue
//
using __etk_mq_t = TX_QUEUE;
#define _ETK_MQ_INITIALIZER                                                    \
    { 0 }

inline _ETK_API_INTERNAL int __etk_mq_init(
    __etk_mq_t* mq,
    size_t capacity,
    size_t message_size,
    void* buffer,
    size_t buffer_size) {
    return tx_queue_create(mq, "etk_mq", message_size, buffer, buffer_size);
}

inline _ETK_API_INTERNAL int
__etk_mq_send(__etk_mq_t* mq, const void* message, size_t message_size) {
    return tx_queue_send(mq, (void*)message, TX_WAIT_FOREVER);
}

inline _ETK_API_INTERNAL bool
__etk_mq_try_send(__etk_mq_t* mq, const void* message, size_t message_size) {
    return tx_queue_send(mq, (void*)message, TX_NO_WAIT) == TX_SUCCESS;
}

inline _ETK_API_INTERNAL int
__etk_mq_receive(__etk_mq_t* mq, void* message, size_t message_size) {
    return tx_queue_receive(mq, message, TX_WAIT_FOREVER);
}

inline _ETK_API_INTERNAL bool
__etk_mq_try_receive(__etk_mq_t* mq, void* message, size_t message_size) {
    return tx_queue_receive(mq, message, TX_NO_WAIT) == TX_SUCCESS;
}

inline _ETK_API_INTERNAL bool __etk_mq_empty(__etk_mq_t* mq) {
    long available_storage;
    tx_queue_info_get(
        mq,
        (const CHAR**)TX_NULL,
        (ULONG*)TX_NULL,
        (ULONG*)&available_storage,
        (TX_THREAD**)TX_NULL,
        (ULONG*)TX_NULL,
        NULL);
    return false;
}

// TODO: Finish this implementation

_ETK_END_NAMESPACE_ETK

#endif // _ETK___MUTEX_SUPPORT_THREADX_H_