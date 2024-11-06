#include "etk/functor.h"
#include <gtest/gtest.h>

int global1, global2;

void funcSet10() { global1 = 10; }

void funcSetArg(int a) { global1 = a; }

void funcSet2Args(int a, int b) {
    global1 = a;
    global2 = b;
}

int funcReturnArg(int a) { return a; }

TEST(Testfunctor, NoArgs) {
    etk::functor f(funcSet10);
    f();
    EXPECT_EQ(global1, 10);
}

TEST(Testfunctor, OneArg) {
    etk::functor f(funcSetArg);
    f(20);
    EXPECT_EQ(global1, 20);
    f(30);
    EXPECT_EQ(global1, 30);
}

TEST(Testfunctor, TwoArgs) {
    etk::functor f(funcSet2Args);
    f(40, 50);
    EXPECT_EQ(global1, 40);
    EXPECT_EQ(global2, 50);
    f(60, 70);
    EXPECT_EQ(global1, 60);
    EXPECT_EQ(global2, 70);
}

TEST(Testfunctor, ReturnArg) {
    etk::functor f(funcReturnArg);
    EXPECT_EQ(f(80), 80);
    EXPECT_EQ(f(90), 90);
}

TEST(Testfunctor, functorCallerNoArgs) {
    etk::functor f(funcSet10);
    etk::functorCaller::call(f);
    EXPECT_EQ(global1, 10);
}

TEST(Testfunctor, functorCallerOneArg) {
    etk::functor f(funcSetArg);
    etk::functor_args args(100);
    etk::functorCaller::call(f, args);
    EXPECT_EQ(global1, 100);
}

TEST(Testfunctor, functorCallerReturnArg) {
    etk::functor f(funcReturnArg);
    etk::functor_args args(110);
    EXPECT_EQ(etk::functorCaller::call(f, args), 110);
}

TEST(Testfunctor, functorCallerTwoArgs) {
    etk::functor f(funcSet2Args);
    etk::functor_args args(120, 130);
    etk::functorCaller::call(f, args);
    EXPECT_EQ(global1, 120);
    EXPECT_EQ(global2, 130);
}

TEST(TestFunctor, FunctorEmpty) {
    etk::functor<void()> f;
    f();
    f = funcSet10;
    f();
    EXPECT_EQ(global1, 10);
}

TEST(TestFunctor, TestLambda) {
    int a = 0;
    etk::functor f([&a]() { a = 10; });
    f();
    EXPECT_EQ(a, 10);
}