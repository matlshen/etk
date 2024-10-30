#include "etk/periodic.h"
#include "etk/thread.h"
#include <gtest/gtest.h>

// TODO: Lower jitter

int last1 = 0;
int last2 = 0;
void task1() {
    unsigned int time = etk::os::time_get();
    printf("Task 1 time: %d\n", time);
    last1 = time;
    etk::this_thread::msleep(50);
}
void task2() {
    printf("        Task 2 time: %d\n", etk::os::time_get());
    etk::this_thread::msleep(100);
}
TEST(TestPeriodic, TestPeriodic) {
    etk::periodic_svc<2> svc;
    svc.add_task(task1, 1000);
    svc.add_task(task2, 500);
    etk::this_thread::msleep(15000);
    svc.stop();
}

// void testFunc() {
//     printf("Task 1\n");
// }
// TEST(TestFunctor, Test1) {
//     etk::functor<void()> f(testFunc);
//     f();
// }