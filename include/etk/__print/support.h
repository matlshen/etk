#ifndef _ETK___PRINT_SUPPORT_H_
#define _ETK___PRINT_SUPPORT_H_

/*
Print implementations must define:

void __etk_vprintf(const char* fmt, va_list* args);
void __etk_vsnprintf(char* buf, size_t n, const char* fmt, va_list* args);
*/

#include "etk/__config.h"

#if defined(_ETK_HAS_PRINT_API_STDIO)
#    include "etk/__print/support/stdio.h"
#elif defined(_ETK_HAS_PRINT_API_RTT)
#    include "etk/__print/support/rtt.h"
#else
#    error "No print API defined"
#endif

#endif /* !_ETK___PRINT_SUPPORT_H_ */