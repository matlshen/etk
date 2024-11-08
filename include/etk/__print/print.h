#ifndef _ETK___PRINT_PRINT_H_
#define _ETK___PRINT_PRINT_H_

#include "etk/__config.h"
#include "etk/__print/support.h"
#include <stdarg.h>

_ETK_BEGIN_NAMESPACE_ETK

inline void printf(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    __etk_vprintf(fmt, &args);
    va_end(args);
}

inline void snprintf(char* buf, size_t n, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    __etk_vsnprintf(buf, n, fmt, &args);
    va_end(args);
}

_ETK_END_NAMESPACE_ETK

#endif /* !_ETK___PRINT_PRINT_H_ */