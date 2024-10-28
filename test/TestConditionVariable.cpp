#include "etk/condition_variable.h"
#include "etk/thread.h"
#include <array>
#include <gtest/gtest.h>

class ConditionVariableTest : public ::testing::Test {
  protected:
    etk::mutex m;
    etk::condition_variable cv;
    int i = 0;
    bool done = false;
};

/**
 * Test that the condition variable can wait and notify one thread
 */
void t1func(etk::mutex &m, etk::condition_variable &cv, int &i, bool &done) {
    etk::unique_lock lock(m);
    cv.wait(lock, [&done]() { return done; });
    EXPECT_EQ(i, 1);
    i = 2;
}
void t2func(etk::mutex &m, etk::condition_variable &cv, int &i, bool &done) {
    etk::this_thread::msleep(1);
    etk::unique_lock lock(m);
    done = true;
    i = 1;
    cv.notify_one();
}
TEST_F(ConditionVariableTest, TestWaitAndNotifyOne) {
    etk::thread t1(t1func, std::ref(m), std::ref(cv), std::ref(i),
                   std::ref(done));
    etk::thread t2(t2func, std::ref(m), std::ref(cv), std::ref(i),
                   std::ref(done));

    t1.join();
    t2.join();

    EXPECT_EQ(i, 2);
}

/**
 * Test that the condition variable can wait and notify multiple threads
 */
void t3func(etk::mutex &m, etk::condition_variable &cv, int &i, bool &done) {
    etk::unique_lock lock(m);
    cv.wait(lock, [&done]() { return done; });
    i++;
}
void t4func(etk::mutex &m, etk::condition_variable &cv, int &i, bool &done) {
    etk::this_thread::msleep(1);
    etk::unique_lock lock(m);
    done = true;
    cv.notify_all();
    (void)i;
}
TEST_F(ConditionVariableTest, TestWaitAndNotifyAll) {
    std::array<etk::thread, 4> threads = {
        etk::thread(t3func, std::ref(m), std::ref(cv), std::ref(i),
                    std::ref(done)),
        etk::thread(t3func, std::ref(m), std::ref(cv), std::ref(i),
                    std::ref(done)),
        etk::thread(t3func, std::ref(m), std::ref(cv), std::ref(i),
                    std::ref(done)),
        etk::thread(t4func, std::ref(m), std::ref(cv), std::ref(i),
                    std::ref(done))};

    for (auto &t : threads) {
        t.join();
    }

    EXPECT_EQ(i, 3);
}