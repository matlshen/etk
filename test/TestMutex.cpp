#include "etk/mutex.h"
#include "etk/thread.h"
#include <gtest/gtest.h>

#include <mutex>

int global;

TEST(TestMutex, MutexCreation) {
    etk::Mutex m;
    m.lock();
    m.unlock();
}

void threadRunner(etk::Mutex *m) {
    m->lock();
    m->unlock();
    m->lock();
    m->unlock();
}
TEST(TestMutex, MutexLock) {
    etk::Mutex m;
    etk::ThreadAttributes attr;
    etk::Thread t1(attr, threadRunner, &m);
    t1.join();
}

void threadRunner2(etk::Mutex *m) {
    bool locked = m->tryLock();
    EXPECT_EQ(locked, true);
    locked = m->tryLock();
    EXPECT_EQ(locked, false);
    m->unlock();
}
TEST(TestMutex, MutexTryLock) {
    etk::Mutex m;
    etk::ThreadAttributes attr;
    etk::Thread t1(attr, threadRunner2, &m);
    t1.join();
}

void uniqueTryLock(etk::Mutex *m) {
    std::unique_lock<etk::Mutex> lock(*m, std::try_to_lock);
    // Random delay
    for (volatile long i = 0; i < 100000; i++)
        ;
    if (lock.owns_lock()) {
        global++;
    }
}
TEST(TestMutex, UniqueLock) {
    global = 0;

    etk::ThreadAttributes attr;
    etk::Mutex m;
    etk::Thread t1(attr, uniqueTryLock, &m);
    etk::Thread t2(attr, uniqueTryLock, &m);

    t1.join();
    t2.join();

    EXPECT_EQ(global, 1);
}