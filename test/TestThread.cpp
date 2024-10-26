#include <gtest/gtest.h>
#include "etk/thread.h"

void testFunc1(int *a, int *b) {
    *b = *a * 2;
}

void testFunc2(const int a, int *b) {
    *b = a * 2;
}

int in, out1, out2;

TEST(TestThread, ThreadCreation) {
    etk::ThreadAttributes attr;
    in = 2;
    out1 = 0;
    out2 = 0;
    etk::Thread t1(attr, testFunc1, &in, &out1);
    etk::Thread t2(attr, testFunc2, 6, &out2);

    EXPECT_EQ(t1.joinable(), true);
    EXPECT_EQ(t2.joinable(), true);
    t1.join();
    t2.join();

    EXPECT_EQ(out1, 4);
    EXPECT_EQ(out2, 12);
}

TEST(TestThread, GetName) {
    etk::ThreadAttributes attr;
    attr.__name = "TestThread";
    etk::Thread t(attr, testFunc1, &in, &out1);

    EXPECT_STREQ(t.getName(), "TestThread");
    t.join();
}

TEST(TestThread, GetId) {
    etk::ThreadAttributes attr;
    etk::Thread t(attr, testFunc1, &in, &out1);

    EXPECT_NE(reinterpret_cast<long>(t.getId()), 0);
    t.join();
}