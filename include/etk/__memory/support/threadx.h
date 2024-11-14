#ifndef _ETK___MEMORY_SUPPORT_STDLIB_H_
#define _ETK___MEMORY_SUPPORT_STDLIB_H_

#include "etk/__config.h"
#include "tx_api.h"

_ETK_BEGIN_NAMESPACE_ETK

struct __etk_mempool_t {
    TX_BYTE_POOL pcb;
    ULONG buffer[_ETK_HEAP_SIZE / sizeof(ULONG)];
};
#define _ETK_MEMPOOL_INITIALIZER                                               \
    { 0 }

inline int __etk_mempool_init(__etk_mempool_t* mempool, size_t size) {
    return tx_byte_pool_create(
        &mempool->pcb, (CHAR*)"etk mempool", (void*)mempool->buffer, size);
}

inline void* __etk_malloc(__etk_mempool_t* mempool, size_t size) {
    void* ptr;
    int ret = tx_byte_allocate(&mempool->pcb, &ptr, size, TX_NO_WAIT);
    if (ret != TX_SUCCESS) {
        return nullptr;
    }
    return ptr;
}

inline void __etk_free(__etk_mempool_t* mempool, void* ptr) {
    (void)mempool;
    tx_byte_release(ptr);
}

_ETK_END_NAMESPACE_ETK

#endif // _ETK___MEMORY_SUPPORT_STDLIB_H_