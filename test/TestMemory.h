#include "etk/unit_test.h"
#include "etk/memory.h"

TEST_SUITE_START(TestMemory)

TEST(TestBasic) {
    CHECK(1 == 1);
}

TEST(TestMemoryMallocFree) {
    void* ptr = etk::memory::malloc(10);
    CHECK(ptr != nullptr);
    etk::memory::free(ptr);
}

TEST(TestMemoryMultipleMalloc) {
    void* ptr = etk::memory::malloc(10);
    void* ptr2 = etk::memory::malloc(10);
    CHECK(ptr != nullptr);
    CHECK(ptr2 != nullptr);
    etk::memory::free(ptr);
    etk::memory::free(ptr2);
}

TEST(TestMemoryMallocFreeLarge) {
    void* ptr = etk::memory::malloc(_ETK_HEAP_SIZE / 2 + 16);
    CHECK(ptr != nullptr);
    etk::memory::free(ptr);

    ptr = nullptr;
    ptr = etk::memory::malloc(_ETK_HEAP_SIZE / 2 + 16);
    CHECK(ptr != nullptr);
    etk::memory::free(ptr);
}

TEST(TestMemoryWriteToMemory) {
    void* ptr = etk::memory::malloc(10);
    CHECK(ptr != nullptr);
    memset(ptr, 37, 10);
    for (int i = 0; i < 10; i++) {
        CHECK(((char*)ptr)[i] == 37);
    }
    etk::memory::free(ptr);
}

TEST_SUITE_END(TestMemory)