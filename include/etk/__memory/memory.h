#ifndef _ETK___MEMORY_MEMORY_H_
#define _ETK___MEMORY_MEMORY_H_

#include "etk/__config.h"
#include "etk/__memory/support.h"
#include "etk/assert.h"

_ETK_BEGIN_NAMESPACE_ETK

/**
 * On first malloc(), initialize the memory pool
 * Subsequient calls to malloc() are passed
 */
class memory {
    static inline __etk_mempool_t _mempool{_ETK_MEMPOOL_INITIALIZER};

    static void* init(size_t size) {
        ASSERT_0(__etk_mempool_init(&_mempool, size));
        _malloc_ptr = internal_malloc;
        return __etk_malloc(&_mempool, size);
    }

    static inline void* internal_malloc(size_t size) {
        return __etk_malloc(&_mempool, size);
    }

    typedef void* (*malloc_ptr_t)(size_t);
    static inline malloc_ptr_t _malloc_ptr{init};

  public:
    static inline void* malloc(size_t size) { return _malloc_ptr(size); }

    static inline void free(void* ptr) { __etk_free(&_mempool, ptr); }
};

_ETK_END_NAMESPACE_ETK

#endif // _ETK___MEMORY_MEMORY_H_