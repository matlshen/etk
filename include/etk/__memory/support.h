#ifndef _ETK___MEMORY_SUPPORT_H_
#define _ETK___MEMORY_SUPPORT_H_

/*
Minimum support API:

using __etk_mempool_t = ...;
#define _ETK_MEMPOOL_INITIALIZER ...

int __etk_mempool_init(__etk_mempool_t*, size_t);
void* __etk_malloc(__etk_mempool_t*, size_t);
void __etk_free(__etk_mempool_t*, void*);
*/

#include "etk/__config.h"

#if !defined(_ETK_HEAP_SIZE)
#    error "_ETK_HEAP_SIZE not defined"
#endif

#if defined(_ETK_HAS_MEMORY_API_STDLIB)
#    include "etk/__memory/support/stdlib.h"
#elif defined(_ETK_HAS_MEMORY_API_THREADX)
#    include "etk/__memory/support/threadx.h"
#else
#    error "No memory API defined"
#endif

#endif // _ETK___MEMORY_SUPPORT_H_