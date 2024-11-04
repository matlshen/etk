#include "etk/active_object.h"
#include <gtest/gtest.h>

static int global1 = 0;

class Adder : public etk::active_object<int, 10> {
  public:
    bool process(int &msg) override {
        global1 += msg;

        if (msg == -1) {
            return false;
        }
        return true;
    }
};

TEST(TestActiveObject, PostTask) {
    Adder ao;
    ao.send(10);
    ao.send(10);
    ao.send(-1);
    ao.join();
    EXPECT_EQ(global1, 19);
}