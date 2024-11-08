#include "etk/mutex.h"
#include "etk/thread.h"
#include "etk/delay.h"
#include <gtest/gtest.h>

int global;

TEST(Testmutex, mutexCreation) {
    etk::mutex m;
    m.lock();
    m.unlock();
}

void threadRunner(etk::mutex *m) {
    m->lock();
    m->unlock();
    m->lock();
    m->unlock();
}
TEST(Testmutex, mutexLock) {
    etk::mutex m;
    etk::thread<1024> t1(threadRunner, &m);
    t1.join();
}

void threadRunner2(etk::mutex *m) {
    bool locked = m->try_lock();
    EXPECT_EQ(locked, true);
    locked = m->try_lock();
    EXPECT_EQ(locked, false);
    m->unlock();
}
TEST(Testmutex, mutexTryLock) {
    etk::mutex m;
    etk::thread<1024> t1(threadRunner2, &m);
    t1.join();
}

void uniqueTryLock(etk::mutex *m) {
    std::unique_lock<etk::mutex> lock(*m, std::try_to_lock);
    // Random delay
    etk::delay::cycles(1000000);
    if (lock.owns_lock()) {
        global++;
    }
}
TEST(Testmutex, unique_lock) {
    global = 0;

    etk::mutex m;
    etk::thread<1024> t1(uniqueTryLock, &m);
    etk::thread<1024> t2(uniqueTryLock, &m);

    t1.join();
    t2.join();

    EXPECT_EQ(global, 1);
}