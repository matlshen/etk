#ifndef _ETK___EVENT_FLAGS_SUPPORT_H_
#define _ETK___EVENT_FLAGS_SUPPORT_H_

/*

_ETK_BEGIN_NAMESPACE_ETK

//
// event flags
//
using __etk_event_flags_t = ...;
#define _ETK_EVENT_FLAGS_INITIALIZER ...

int event_flags_create(__etk_event_flags_t*);
int event_flags_set(__etk_event_flags_t*, uint32_t);
int event_flags_clear(__etk_event_flags_t*, uint32_t);
int event_flags_get(__etk_event_flags_t*, uint32_t*, event_flags::mode);
int event_flags_destroy(__etk_event_flags_t*);

_ETK_END_NAMESPACE_ETK

*/

#include "etk/__config.h"

#if defined(_ETK_HAS_THREAD_API_THREADX)
#include "etk/__event_flags/support/threadx.h"
#endif

#endif // _ETK___EVENT_FLAGS_SUPPORT_H_