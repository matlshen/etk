#include "etk/mutex.h"
#include "etk/thread.h"
#include <gtest/gtest.h>

#include <mutex>

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
    etk::thread_attributes attr;
    etk::thread t1(attr, threadRunner, &m);
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
    etk::thread_attributes attr;
    etk::thread t1(attr, threadRunner2, &m);
    t1.join();
}

void uniqueTryLock(etk::mutex *m) {
    std::unique_lock<etk::mutex> lock(*m, std::try_to_lock);
    // Random delay
    for (volatile long i = 0; i < 100000; i++)
        ;
    if (lock.owns_lock()) {
        global++;
    }
}
TEST(Testmutex, unique_lock) {
    global = 0;

    etk::thread_attributes attr;
    etk::mutex m;
    etk::thread t1(attr, uniqueTryLock, &m);
    etk::thread t2(attr, uniqueTryLock, &m);

    t1.join();
    t2.join();

    EXPECT_EQ(global, 1);
}