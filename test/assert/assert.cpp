#include "etk/assert.h"
#include <iostream>

/*
Expect failures on lines: 22, 27, 40, 53, 66, 79, 92, 105, 118, 123
*/

int func(int ret) { return ret; }

void testAssert() {
    // Passing
    ASSERT(1);
    ASSERT_FAIL(1);
    ASSERT(1 == 1);
    ASSERT_FAIL(1 == 1);
    ASSERT(true);
    ASSERT_FAIL(true);

    // Failing
    ASSERT_MSG(func(0), "func(0) failed");
}

void testUnreachable() {
    // Failing
    ASSERT_UNREACHABLE();
}

void test0() {
    // Passing
    ASSERT_0(0);
    ASSERT_0_FAIL(0);
    ASSERT_0(false);
    ASSERT_0_FAIL(false);
    ASSERT_0(func(0));
    ASSERT_0_FAIL(func(0));

    // Failing
    ASSERT_0(1);
}

void testEq() {
    // Passing
    ASSERT_EQ(0, 0);
    ASSERT_EQ_FAIL(0, 0);
    ASSERT_EQ(1, 1);
    ASSERT_EQ_FAIL(1, 1);
    ASSERT_EQ(func(0), 0);
    ASSERT_EQ_FAIL(func(0), 0);

    // Failing
    ASSERT_EQ(0, 1);
}

void testNeq() {
    // Passing
    ASSERT_NE(0, 1);
    ASSERT_NE_FAIL(0, 1);
    ASSERT_NE(1, 0);
    ASSERT_NE_FAIL(1, 0);
    ASSERT_NE(func(0), 1);
    ASSERT_NE_FAIL(func(0), 1);

    // Failing
    ASSERT_NE(1234, 1234);
}

void testLt() {
    // Passing
    ASSERT_LT(0, 1);
    ASSERT_LT_FAIL(0, 1);
    ASSERT_LT(1, 2);
    ASSERT_LT_FAIL(1, 2);
    ASSERT_LT(func(0), 1);
    ASSERT_LT_FAIL(func(0), 1);

    // Failing
    ASSERT_LT(1, 1);
}

void testLe() {
    // Passing
    ASSERT_LE(0, 1);
    ASSERT_LE_FAIL(0, 1);
    ASSERT_LE(1, 1);
    ASSERT_LE_FAIL(1, 1);
    ASSERT_LE(func(0), 1);
    ASSERT_LE_FAIL(func(0), 1);

    // Failing
    ASSERT_LE(1, 0);
}

void testGt() {
    // Passing
    ASSERT_GT(1, 0);
    ASSERT_GT_FAIL(1, 0);
    ASSERT_GT(2, 1);
    ASSERT_GT_FAIL(2, 1);
    ASSERT_GT(func(1), 0);
    ASSERT_GT_FAIL(func(1), 0);

    // Failing
    ASSERT_GT(1, 1);
}

void testGe() {
    // Passing
    ASSERT_GE(1, 0);
    ASSERT_GE_FAIL(1, 0);
    ASSERT_GE(1, 1);
    ASSERT_GE_FAIL(1, 1);
    ASSERT_GE(func(1), 0);
    ASSERT_GE_FAIL(func(1), 0);

    // Failing
    ASSERT_GE(0, 1);
}

void testFail() {
    // Failing
    ASSERT_MSG_FAIL(func(0), "func(0) failed");
}

int main() {
    testAssert();
    testUnreachable();
    test0();
    testEq();
    testNeq();
    testLt();
    testLe();
    testGt();
    testGe();

    testFail();

    return 0;
}