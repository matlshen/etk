#ifndef _ETK___ASSERT_ASSERT_H_
#define _ETK___ASSERT_ASSERT_H_

#include "debugbreak.h"
#include "etk/__config.h"
#include "etk/__print/print.h"
#include "getpc.h"

#define STRINGIFY(x) #x
#define TO_STRING(x) STRINGIFY(x)

_ETK_BEGIN_NAMESPACE_ETK

class __assertion_helper {
  public:
    static void __assert_minimal() { debug_break(); }

    static inline void __assert_pc(const char* line, void* assert_pc) {
        etk::printf("*** ASSERTION FAILED ***\n\tLine: %s\n\tPC: 0x%08lx\n",
                    line,
                    reinterpret_cast<uintptr_t>(assert_pc));
        debug_break();
    }

    static inline void
    __assert_verbose(const char* expr, const char* file, const char* line) {
        etk::printf("*** ASSERTION FAILED ***\n\tExpression:\t%s\n\t%s: %s\n",
                    expr,
                    file,
                    line);
        debug_break();
    }
};

_ETK_END_NAMESPACE_ETK

#if defined(_ETK_ASSERT_NONE)
#    define ASSERT(expr) (void)(expr)
#elif defined(_ETK_ASSERT_BREAK)
#    define ASSERT(expr)                                                       \
        if (!(expr)) {                                                         \
            etk::__assertion_helper::__assert_minimal();                       \
        }
#elif defined(_ETK_ASSERT_PC)
#    define ASSERT(expr)                                                       \
        if (!(expr)) {                                                         \
            void* pc;                                                          \
            GET_PC(pc);                                                        \
            etk::__assertion_helper::__assert_pc(TO_STRING(__LINE__), pc);     \
        }
#elif defined(_ETK_ASSERT_VERBOSE)
#    define ASSERT(expr)                                                       \
        if (!(expr)) {                                                         \
            etk::__assertion_helper::__assert_verbose(                         \
                #expr, __FILE__, TO_STRING(__LINE__));                         \
        }
#else
#    error "No assert configuration defined"
#endif

#define STATIC_ASSERT_MSG(expr, msg) static_assert(expr, msg)
#define STATIC_ASSERT(expr) static_assert(expr, #expr)

#endif // _ETK___ASSERT_ASSERT_H_