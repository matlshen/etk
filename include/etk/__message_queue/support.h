#ifndef _ETK___MESSAGE_QUEUE_SUPPORT_H_
#define _ETK___MESSAGE_QUEUE_SUPPORT_H_

#include "etk/__config.h"

/*

_ETK_BEGIN_NAMESPACE_ETK

//
// Message Queue
//
using __etk_mq_t = ...;
#define _ETK_MQ_INITIALIZER ...

int __etk_mq_init(__etk_mq_t*, size_t, size_t, void*, size_t);
int __etk_mq_send(__etk_mq_t*, const void*, size_t);
bool __etk_mq_try_send(__etk_mq_t*, const void*, size_t);
int __etk_mq_receive(__etk_mq_t*, void*, size_t);
bool __etk_mq_try_receive(__etk_mq_t*, void*, size_t);
bool __etk_mq_empty(__etk_mq_t*);
int __etk_mq_size(const __etk_mq_t*);
int __etk_mq_capacity(const __etk_mq_t*);
int __etk_mq_destroy(__etk_mq_t*);

_ETK_END_NAMESPACE_ETK
*/

#if defined(_ETK_HAS_THREAD_API_APPLE)
#    include "etk/__thread/support/apple.h"
#elif defined(_ETK_HAS_THREAD_API_THREADX)
#    include "etk/__thread/support/threadx.h"
#else
#    error "No thread support API defined"
#endif

#endif // _ETK___MESSAGE_QUEUE_SUPPORT_H_