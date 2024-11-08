#ifndef _ETK___MEMORY_SUPPORT_STDLIB_H_
#define _ETK___MEMORY_SUPPORT_STDLIB_H_

#include "etk/__config.h"
#include <stddef.h>
#include <stdlib.h>

_ETK_BEGIN_NAMESPACE_ETK

// Not used
typedef int __etk_mempool_t;
#define _ETK_MEMPOOL_INITIALIZER 0

inline int __etk_mempool_init(__etk_mempool_t* mempool, size_t size) {
    (void)mempool;
    (void)size;
    return 0;
}

inline void* __etk_malloc(__etk_mempool_t* mempool, size_t size) {
    (void)mempool;
    return malloc(size);
}

inline void __etk_free(__etk_mempool_t* mempool, void* ptr) {
    (void)mempool;
    free(ptr);
}

_ETK_END_NAMESPACE_ETK

#endif // _ETK___MEMORY_SUPPORT_STDLIB_H_