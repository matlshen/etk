#ifndef __ETK___LOG_LOG_H__
#define __ETK___LOG_LOG_H__

#include "etk/__config.h"
#include "etk/__log/support.h"

_ETK_BEGIN_NAMESPACE_ETK


class log {
public:
    enum level {
        FATAL = 0;
        ERROR = 1;
        WARN = 2;
        INFO = 3;
        DEBUG = 4;
    };
    
    static bool set_level(int level) {
        return __etk_set_log_level(level);
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