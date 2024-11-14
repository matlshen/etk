#include "etk/print.h"
#include <gtest/gtest.h>

// Does not test all formats, basically just passing through function to
// native snprintf
TEST(TestPrint, BasicPrint) {
    char buffer[100];
    etk::snprintf(buffer, sizeof(buffer), "Hello, World");
    EXPECT_STREQ(buffer, "Hello, World");
}

TEST(TestPrint, StringPrint) {
    char buffer[100];
    etk::snprintf(buffer, sizeof(buffer), "Hello, %s", "World");
    EXPECT_STREQ(buffer, "Hello, World");
}

TEST(TestPrint, IntegerPrint) {
    char buffer[100];
    etk::snprintf(buffer, sizeof(buffer), "Hello, %d", 42);
    EXPECT_STREQ(buffer, "Hello, 42");
}