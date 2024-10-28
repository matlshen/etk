#include "etk/thread.h"
#include <gtest/gtest.h>

void testFunc1(int *a, int *b) { *b = *a * 2; }

void testFunc2(const int a, int *b) { *b = a * 2; }

int in, out1, out2;

TEST(Testthread, threadCreation) {
    etk::thread_attributes attr;
    in = 2;
    out1 = 0;
    out2 = 0;
    etk::thread t1(attr, testFunc1, &in, &out1);
    etk::thread t2(attr, testFunc2, 6, &out2);

    EXPECT_EQ(t1.joinable(), true);
    EXPECT_EQ(t2.joinable(), true);
    t1.join();
    t2.join();

    EXPECT_EQ(out1, 4);
    EXPECT_EQ(out2, 12);
}

TEST(Testthread, GetName) {
    etk::thread_attributes attr;
    attr.__name = "Testthread";
    etk::thread t(attr, testFunc1, &in, &out1);

    EXPECT_STREQ(t.get_name(), "Testthread");
    t.join();
}

TEST(Testthread, GetId) {
    etk::thread_attributes attr;
    etk::thread t(attr, testFunc1, &in, &out1);

    EXPECT_NE(reinterpret_cast<long>(t.get_id()), 0);
    t.join();
}

TEST(TestThread, Sleep) {
    etk::thread_attributes attr;
    etk::thread t1(attr, etk::this_thread::msleep, 10);
    etk::thread t2(attr, etk::this_thread::usleep, 10000);
    t1.join();
    t2.join();
}