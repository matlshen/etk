#include "etk/semaphore.h"
#include "etk/thread.h"
#include <gtest/gtest.h>

class SemaphoreTest : public ::testing::Test {
  protected:
    etk::counting_semaphore sem{1};
    int global = 0;
};

void waitFunc(etk::counting_semaphore &sem) {
    sem.wait();
}
TEST_F(SemaphoreTest, TestWait) {
    etk::thread t1(waitFunc, std::ref(sem));
    t1.join();
}

void tryWaitFunc(etk::counting_semaphore &sem) {
    bool locked = sem.try_wait();
    EXPECT_EQ(locked, true);
    locked = sem.try_wait();
    EXPECT_EQ(locked, false);
}
TEST_F(SemaphoreTest, TestTryWait) {
    etk::thread t1(tryWaitFunc, std::ref(sem));
    t1.join();
}

void signalFunc(etk::counting_semaphore &sem) {
    sem.signal();
}
TEST_F(SemaphoreTest, TestSignal) {
    sem.wait();
    etk::thread t1(waitFunc, std::ref(sem));
    etk::thread t2(signalFunc, std::ref(sem));
    t1.join();
    t2.join();
}

TEST_F(SemaphoreTest, TestBinary) {
    etk::binary_semaphore sem(1);
    sem.signal();
    sem.signal();
    EXPECT_EQ(sem.try_wait(), true);
    EXPECT_EQ(sem.try_wait(), false);
}