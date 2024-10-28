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