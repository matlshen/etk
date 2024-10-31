#ifndef _ETK___LOG_SUPPORT_RTT_H_
#define _ETK___LOG_SUPPORT_RTT_H_

#include "SEGGER_RTT.h"
#include "etk/__thread/this_thread.h"

inline int __etk_sys_log_level = 0;

inline void __etk_set_log_level(int level) { __etk_sys_log_level = level; }

inline int __etk_get_log_level() { return __etk_sys_log_level; }

inline void __etk_log(int level, const char *fmt, va_list *args) {
    if (level > __etk_sys_log_level) {
        return;
    }

    switch (level) {
    case 0:
        SEGGER_RTT_Write(0, "[FATAL] ", 8);
        break;
    case 1:
        SEGGER_RTT_Write(0, "[ERROR] ", 8);
        break;
    case 2:
        SEGGER_RTT_Write(0, "[WARN] ", 7);
        break;
    case 3:
        SEGGER_RTT_Write(0, "[INFO] ", 7);
        break;
    case 4:
        SEGGER_RTT_Write(0, "[DEBUG] ", 8);
        break;
    default:
        break;
    }

#if !defined(_ETK_HAS_THREAD_API_NONE)
    SEGGER_RTT_printf(0, "[%d] ", etk::os::time_get());
#endif

    SEGGER_RTT_vprintf(0, fmt, args);

    SEGGER_RTT_Write(0, "\n", 1);
}

#endif // _ETK___LOG_SUPPORT_RTT_H_