#ifndef _ETK___LOG_SUPPORT_RTT_H_
#define _ETK___LOG_SUPPORT_RTT_H_

#include <stdarg.h>

inline bool __etk_set_log_level(int level) {
    (void)level;
    return true;
}

inline int __etk_get_log_level() { return 0; }

inline void __etk_log(int level, const char* fmt, va_list* args) {
    (void)level;
    (void)fmt;
    (void)args;
}

#endif // _ETK___LOG_SUPPORT_RTT_H_