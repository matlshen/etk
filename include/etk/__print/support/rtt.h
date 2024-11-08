#ifndef _ETK___PRINT_SUPPORT_RTT_H_
#define _ETK___PRINT_SUPPORT_RTT_H_

#include "SEGGER_RTT.h"
#include "etk/__config.h"

_ETK_BEGIN_NAMESPACE_ETK

inline _ETK_API_INTERNAL void __etk_vprintf(const char* fmt, va_list* args) {
    SEGGER_RTT_vprintf(0, fmt, args);
}

inline _ETK_API_INTERNAL void
__etk_vsnprintf(char* buf, size_t n, const char* fmt, va_list* args) {
    (void)buf;
    (void)n;
    (void)fmt;
    (void)args;
    return; // Not implemented for RTT
}

_ETK_END_NAMESPACE_ETK

#endif /* !_ETK___PRINT_SUPPORT_RTT_H_ */