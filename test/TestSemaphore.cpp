#include "etk/semaphore.h"
#include "etk/thread.h"
#include "etk/delay.h"
#include <gtest/gtest.h>


class SemaphoreTest : public ::testing::Test {
  protected:
    int global = 0;
};

TEST_F(SemaphoreTest, TestMax) {
    std::counting_semaphore<45> sem(0);
    EXPECT_EQ(45, sem.max());
    std::binary_semaphore sem2(0);
    EXPECT_EQ(1, sem2.max());
}

TEST_F(SemaphoreTest, TestAcquire) {
    std::counting_semaphore<2> sem(2);
    sem.acquire();
    sem.acquire();
    // EXPECT_EQ(0, sem.count());
    sem.release();
    sem.release();
    etk::delay::cycles(1000000);
    sem.acquire();
    sem.acquire();
}

TEST_F(SemaphoreTest, TestTryAcquire) {
    std::counting_semaphore<2> sem(0);
    EXPECT_EQ(false, sem.try_acquire());
    EXPECT_EQ(false, sem.try_acquire());
    sem.release();
    EXPECT_EQ(true, sem.try_acquire());
    EXPECT_EQ(false, sem.try_acquire());
    sem.release();
    sem.release();
    EXPECT_EQ(true, sem.try_acquire());
    EXPECT_EQ(true, sem.try_acquire());
    EXPECT_EQ(false, sem.try_acquire());
}

TEST_F(SemaphoreTest, TestGetCount) {
    std::counting_semaphore<2> sem(2);
    // EXPECT_EQ(2, sem.count());
    sem.acquire();
    // EXPECT_EQ(1, sem.count());
    sem.acquire();
    // EXPECT_EQ(0, sem.count());
    sem.release();
    // EXPECT_EQ(1, sem.count());
}

TEST_F(SemaphoreTest, TestTooManyRelease) {
    std::counting_semaphore<3> sem(0);
    sem.release();
    sem.release();
    sem.release();
    // EXPECT_EQ(3, sem.count());
    sem.release();
    // EXPECT_EQ(3, sem.count());
}

void acquireThread(std::counting_semaphore<2> *sem, int *global) {
    sem->acquire();
    sem->acquire();
    *global = 1;
}
TEST_F(SemaphoreTest, TestAcquireThread) {
    std::counting_semaphore<2> sem(2);
    std::thread t1(acquireThread, &sem, &global);
    sem.release();
    sem.release();
    t1.join();
    EXPECT_EQ(1, global);
}

void thread1(std::counting_semaphore<2> *sem, int *global) {
    etk::delay::cycles(1000000);
    *global = 1;
    sem->release();
    sem->release();
}
void thread2(std::counting_semaphore<2> *sem, int *global) {
    sem->acquire();
    sem->acquire();
    EXPECT_EQ(1, *global);
    *global = 3;
}
TEST_F(SemaphoreTest, TestBlocking) {
    std::counting_semaphore<2> sem(0);
    std::thread t1(thread1, &sem, &global);
    std::thread t2(thread2, &sem, &global);
    t1.join();
    t2.join();
    EXPECT_EQ(3, global);
}
