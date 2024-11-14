#include "etk/delay.h"
#include "etk/thread.h"
#include "etk/unit_test.h"

static inline int global = 0;

static void thread_func(int i) { global = i; }

TEST_SUITE_START(TestThread)

TEST(TestBasic) {
    etk::thread t(etk::priority::normal, 1024, thread_func, 24);
    t.join();
    CHECK(global == 24);
}

TEST(GetName) {
    etk::thread t(
        "thread1", etk::priority::above_normal, 1024, thread_func, 42);
    CHECK(strcmp(t.get_name(), "thread1") == 0);
    t.join();
}

TEST(GetId) {
    etk::thread t(
        "thread2", etk::priority::above_normal, 1024, thread_func, 42);
    CHECK(t.get_id() != 0);
    t.join();
}

TEST(Sleep) {
    etk::thread t1(
        etk::priority::above_normal, 1024, etk::this_thread::msleep, 10);
    etk::thread t2(
        etk::priority::above_normal, 1024, etk::this_thread::usleep, 10000);
    t1.join();
    t2.join();
}

TEST_SUITE_END(TestThread)