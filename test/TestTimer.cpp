#include "etk/timer.h"
#include <gtest/gtest.h>

// TODO: Add test for jitter
// TODO: Find a way to unlock mutex before deletion

namespace no_task {
TEST(TestTimer, NoTask) {
    etk::timer<1024, 5> t;
    etk::this_thread::msleep(2);
}
}

namespace one_task {
void task(void *arg) {
    int* global = reinterpret_cast<int *>(arg);
    (*global)++;
}
TEST(TestTimer, OneTask) {
    etk::os::time_start();
    int global = 0;
    etk::timer<1024, 5> t(etk::priority::low);
    t.add_task(task, (void *)&global, 0, 3);
    etk::this_thread::msleep(10);
    EXPECT_EQ(global, 4);
}
}

// This is as fast as I could run this test on macOS
namespace two_tasks {
int global1 = 0;
int global2 = 0;

void task1(void *arg) {
    (void)arg;
    // std::cout << "task1 time: " << etk::os::time_get() << std::endl;
    global1++;
}
void task2(void *arg) {
    (void)arg;
    // std::cout << "task2 time: " << etk::os::time_get() << std::endl;
    global2++;
}

TEST(TestTimer, TwoTasks) {
    etk::os::time_start();
    etk::timer<1024, 5> t(etk::priority::low);
    t.add_task(task1, (void *)&global1, 0, 6);
    t.add_task(task2, (void *)&global2, 14, 14);
    etk::this_thread::msleep(30);
    EXPECT_EQ(global1, 6);
    EXPECT_EQ(global2, 2);
}
}