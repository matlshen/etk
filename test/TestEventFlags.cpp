#include "etk/__thread/thread.h"
#include "etk/event_flags.h"
#include "etk/delay.h"
#include <gtest/gtest.h>

TEST(EventFlagsTest, SetFlag) {
    etk::event_flags flags;
    flags.set(1);
    EXPECT_EQ(flags.wait(1, etk::event_flags::wait_any), 1);
}

TEST(EventFlagsTest, ClearFlag) {
    etk::event_flags flags;
    flags.set(0b11);
    flags.clear(0b10);
    EXPECT_EQ(flags.wait(0b01, etk::event_flags::wait_any), 0b01);
}

TEST(EventFlagsTest, WaitAll) {
    etk::event_flags flags;
    flags.set(0b11);
    EXPECT_EQ(flags.wait(0b11, etk::event_flags::wait_all), 0b11);
}

namespace WaitAllThread {
void wait_thread(etk::event_flags &flags) {
    flags.wait(0b11, etk::event_flags::wait_all);
}
TEST(EventFlagsTest, WaitAllThread) {
    etk::event_flags flags;
    etk::thread t(wait_thread, std::ref(flags));
    flags.set(0b01);
    flags.set(0b10);
    t.join();
}
} // WaitAllThread

namespace WakeMultiple {
void wait_thread1(etk::event_flags *flags, etk::mutex *m, int *var) {
    flags->wait(0b11, etk::event_flags::wait_any);
    etk::unique_lock<etk::mutex> lock(*m);
    (*var)++;
}
void wait_thread2(etk::event_flags *flags, etk::mutex *m, int *var) {
    flags->wait(0b11, etk::event_flags::wait_any);
    etk::unique_lock<etk::mutex> lock(*m);
    (*var)++;
}
TEST(EventFlagsTest, WakeMultiple) {
    etk::mutex m;
    etk::event_flags flags;
    int global = 0;
    etk::thread t1(wait_thread1, &flags, &m, &global);
    etk::thread t2(wait_thread2, &flags, &m, &global);
    flags.set(0b01);
    t1.join();
    t2.join();
    EXPECT_EQ(global, 2);
}
} // WakeMultiple

namespace WakeMultipleClear {
void wait_thread(etk::event_flags *flags, int *var) {
    flags->wait(0b11, etk::event_flags::wait_any_clear);
    *var += 1;
}
TEST(EventFlagsTest, WakeMultipleClear) {
    etk::event_flags flags;
    int global = 0;
    etk::thread t1(wait_thread, &flags, &global);
    etk::thread t2(wait_thread, &flags, &global);
    flags.set(0b01);
    etk::delay::cycles(1000000);
    EXPECT_EQ(global, 1);
    flags.set(0b01);
    t1.join();
    t2.join();
    EXPECT_EQ(global, 2);
}
} // WakeMultipleClear