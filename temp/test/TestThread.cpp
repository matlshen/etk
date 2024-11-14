#include "etk/thread.h"
#include <gtest/gtest.h>

void testFunc1(int *a, int *b) { *b = *a * 2; }

void testFunc2(const int a, int *b) { *b = a * 2; }

int in, out1, out2;

TEST(Testthread, threadCreation) {
    // etk::thread_attributes attr;
    in = 2;
    out1 = 0;
    out2 = 0;
    etk::thread<4096> t1(testFunc1, &in, &out1);
    etk::thread<4096> t2(testFunc2, 6, &out2);

    EXPECT_EQ(t1.joinable(), true);
    EXPECT_EQ(t2.joinable(), true);
    t1.join();
    t2.join();

    EXPECT_EQ(out1, 4);
    EXPECT_EQ(out2, 12);
}

TEST(Testthread, GetName) {
    etk::thread<1024> t("thread1", etk::priority::above_normal, testFunc1, &in,
                        &out1);

    EXPECT_STREQ(t.get_name(), "thread1");
    t.join();
}

TEST(Testthread, GetId) {
    etk::thread<1024> t(testFunc1, &in, &out1);

    EXPECT_NE(reinterpret_cast<unsigned long>(t.get_id()), 0);
    t.join();
}

TEST(TestThread, Sleep) {
    etk::thread<1024> t1(etk::this_thread::msleep, 10);
    etk::thread<1024> t2(etk::this_thread::usleep, 10000);
    t1.join();
    t2.join();
}