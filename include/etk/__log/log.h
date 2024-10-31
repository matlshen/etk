#ifndef __ETK___LOG_LOG_H__
#define __ETK___LOG_LOG_H__

#include "etk/__config.h"
#include "etk/__log/support.h"

_ETK_BEGIN_NAMESPACE_ETK



class log {
public:
    static constexpr int FATAL_LVL = 0;
    static constexpr int ERROR_LVL = 1;
    static constexpr int WARN_LVL = 2;
    static constexpr int INFO_LVL = 3;
    static constexpr int DEBUG_LVL = 4;
    
    static void set_level(int level) {
        __etk_set_log_level(level);
    }

    static int get_level() {
        return __etk_get_log_level();
    }

    static void fatal(const char* fmt, ...) {
        va_list args;
        va_start(args, fmt);
        __etk_log(FATAL_LVL, fmt, &args);
        va_end(args);
    }

    static void error(const char* fmt, ...) {
        va_list args;
        va_start(args, fmt);
        __etk_log(ERROR_LVL, fmt, &args);
        va_end(args);
    }

    static void warn(const char* fmt, ...) {
        va_list args;
        va_start(args, fmt);
        __etk_log(WARN_LVL, fmt, &args);
        va_end(args);
    }

    static void info(const char* fmt, ...) {
        va_list args;
        va_start(args, fmt);
        __etk_log(INFO_LVL, fmt, &args);
        va_end(args);
    }

    static void debug(const char* fmt, ...) {
        va_list args;
        va_start(args, fmt);
        __etk_log(DEBUG_LVL, fmt, &args);
        va_end(args);
    }
};

_ETK_END_NAMESPACE_ETK

#endif // __ETK___LOG_LOG_H__