#include "etk/memory.h"
#include <gtest/gtest.h>

TEST(TestMemory, MallocFree) {
    void* ptr = etk::memory::malloc(10);
    EXPECT_NE(ptr, nullptr);
    etk::memory::free(ptr);
}

TEST(TestMemory, MutlipleMalloc) {
    void* ptr = etk::memory::malloc(10);
    std::cout << "ptr: " << ptr << std::endl;
    void* ptr2 = etk::memory::malloc(10);
    std::cout << "ptr2: " << ptr2 << std::endl;
    EXPECT_NE(ptr, nullptr);
    EXPECT_NE(ptr2, nullptr);
    etk::memory::free(ptr);
    etk::memory::free(ptr2);
}

TEST(TestMemory, MallocFreeLarge) {
    void* ptr = etk::memory::malloc(1024);
    EXPECT_NE(ptr, nullptr);
    etk::memory::free(ptr);
}

TEST(TestMemory, WriteToMemory) {
    void* ptr = etk::memory::malloc(10);
    EXPECT_NE(ptr, nullptr);
    memset(ptr, 37, 10);
    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(((char*)ptr)[i], 37);
    }
    etk::memory::free(ptr);
}