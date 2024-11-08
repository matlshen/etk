#ifndef __ETK___PRINT_SUPPORT_STDIO_H_
#define __ETK___PRINT_SUPPORT_STDIO_H_

#include "etk/__config.h"
#include <stdio.h>

_ETK_BEGIN_NAMESPACE_ETK

inline _ETK_API_INTERNAL void __etk_vprintf(const char* fmt, va_list* args) {
    vprintf(fmt, *args);
}

inline _ETK_API_INTERNAL void
__etk_vsnprintf(char* buf, size_t n, const char* fmt, va_list* args) {
    vsnprintf(buf, n, fmt, *args);
}

_ETK_END_NAMESPACE_ETK

#endif /* !__ETK___PRINT_SUPPORT_STDIO_H_ */