#ifndef _ETK_DELAY_H_
#define _ETK_DELAY_H_

#include "etk/__config.h"
#include <cstdint>

_ETK_BEGIN_NAMESPACE_ETK

class delay {
  public:
    static void cycles(uint64_t cycles) {
        // ++ operator on volatile type deprecated in C++ 20
        for (; cycles > 0; cycles--) {
            asm volatile("nop");
        }
    }
};

_ETK_END_NAMESPACE_ETK

#endif // _ETK_DELAY_H_