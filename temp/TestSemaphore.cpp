#include "etk/semaphore.h"
#include "etk/thread.h"
#include <gtest/gtest.h>

class SemaphoreTest : public ::testing::Test {
  protected:
    int global = 0;
};

TEST_F(SemaphoreTest, TestMax) {
    etk::counting_semaphore<45> sem(0);
    EXPECT_EQ(45, sem.max());
    etk::binary_semaphore sem2(0);
    EXPECT_EQ(1, sem2.max());
}

TEST_F(SemaphoreTest, TestAcquire) {
    etk::counting_semaphore<2> sem(2);
    sem.acquire();
    sem.acquire();
    sem.release();
    sem.release();
    sem.acquire();
    sem.acquire();
}

TEST_F(SemaphoreTest, TestTryAcquire) {
    etk::counting_semaphore<2> sem(0);
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
    etk::counting_semaphore<2> sem(2);
    EXPECT_EQ(2, sem.count());
    sem.acquire();
    EXPECT_EQ(1, sem.count());
    sem.acquire();
    EXPECT_EQ(0, sem.count());
    sem.release();
    EXPECT_EQ(1, sem.count());
}

TEST_F(SemaphoreTest, TestTooManyRelease) {
    etk::counting_semaphore<3> sem(0);
    sem.release();
    sem.release();
    sem.release();
    EXPECT_EQ(3, sem.count());
    sem.release();
    EXPECT_EQ(3, sem.count());
}

void acquireThread(etk::counting_semaphore<2> *sem, int *global) {
    sem->acquire();
    sem->acquire();
    *global = 1;
}
TEST_F(SemaphoreTest, TestAcquireThread) {
    etk::counting_semaphore<2> sem(2);
    etk::thread t1(acquireThread, &sem, &global);
    sem.release();
    sem.release();
    t1.join();
    EXPECT_EQ(1, global);
}

void thread1(etk::counting_semaphore<2> *sem, int *global) {
    for (volatile int i = 0; i < 1000000; i++);
    *global = 1;
    sem->release();
    sem->release();
}
void thread2(etk::counting_semaphore<2> *sem, int *global) {
    sem->acquire();
    sem->acquire();
    EXPECT_EQ(1, *global);
    *global = 3;
}
TEST_F(SemaphoreTest, TestBlocking) {
    etk::counting_semaphore<2> sem(0);
    etk::thread t1(thread1, &sem, &global);
    etk::thread t2(thread2, &sem, &global);
    t1.join();
    t2.join();
    EXPECT_EQ(3, global);
}
