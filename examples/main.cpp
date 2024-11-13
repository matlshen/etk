#include <gtest/gtest.h>
#include "etk/print.h"

TEST(ExampleTest, Example) {
    EXPECT_EQ(1, 1);
}

TEST(ExampleTest, Example2) {
    EXPECT_EQ(1, 1);
}

class TestPrinter : public ::testing::EmptyTestEventListener {
    virtual void OnTestStart(const ::testing::TestInfo& test_info) {
        printf("*** Test [%s.%s] starting...\n",
            test_info.test_suite_name(), test_info.name());
    }
    virtual void OnTestEnd(const ::testing::TestInfo& test_info) {
        if (test_info.result()->Passed()) {
            printf("    Passed.\n");
        } else
        if (test_info.result()->Failed()) {
            printf("    Failed.\n");
        }
    }
};

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);

    testing::TestEventListeners& listeners = testing::UnitTest::GetInstance()->listeners();
    delete listeners.Release(listeners.default_result_printer());
    listeners.Append(new TestPrinter);

    return RUN_ALL_TESTS();
}