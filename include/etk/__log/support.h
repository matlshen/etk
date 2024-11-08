#ifndef _ETK___LOG_SUPPORT_H_
#define _ETK___LOG_SUPPORT_H_

#include "etk/__config.h"

/*
This library provides support for multiple logging implementations. On POSIX
system logs are simply written to stderr.

The following functionality must be provided by any implementation:

_ETK_BEGIN_NAMESPACE_ETK

void __etk_set_log_level(int level);
int __etk_get_log_level();
void __etk_log(int level, const char* fmt, ...);

_ETK_END_NAMESPACE_ETK
*/

#if defined(_ETK_HAS_LOG_API_NONE)
#    include "etk/__log/support/none.h"
#elif defined(_ETK_HAS_LOG_API_RTT)
#    include "etk/__log/support/RTT.h"
#else
#    error "No logging API defined"
#endif

#endif // _ETK___LOG_SUPPORT_H_