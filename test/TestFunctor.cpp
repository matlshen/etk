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

TEST(TestFunctor, NoArgs) {
    etk::Functor f(funcSet10);
    f();
    EXPECT_EQ(global1, 10);
}

TEST(TestFunctor, OneArg) {
    etk::Functor f(funcSetArg);
    f(20);
    EXPECT_EQ(global1, 20);
    f(30);
    EXPECT_EQ(global1, 30);
}

TEST(TestFunctor, TwoArgs) {
    etk::Functor f(funcSet2Args);
    f(40, 50);
    EXPECT_EQ(global1, 40);
    EXPECT_EQ(global2, 50);
    f(60, 70);
    EXPECT_EQ(global1, 60);
    EXPECT_EQ(global2, 70);
}

TEST(TestFunctor, ReturnArg) {
    etk::Functor f(funcReturnArg);
    EXPECT_EQ(f(80), 80);
    EXPECT_EQ(f(90), 90);
}

TEST(TestFunctor, FunctorCallerNoArgs) {
    etk::Functor f(funcSet10);
    etk::FunctorCaller::call(f);
    EXPECT_EQ(global1, 10);
}

TEST(TestFunctor, FunctorCallerOneArg) {
    etk::Functor f(funcSetArg);
    etk::FunctorArgs args(100);
    etk::FunctorCaller::call(f, args);
    EXPECT_EQ(global1, 100);
}

TEST(TestFunctor, FunctorCallerReturnArg) {
    etk::Functor f(funcReturnArg);
    etk::FunctorArgs args(110);
    EXPECT_EQ(etk::FunctorCaller::call(f, args), 110);
}

TEST(TestFunctor, FunctorCallerTwoArgs) {
    etk::Functor f(funcSet2Args);
    etk::FunctorArgs args(120, 130);
    etk::FunctorCaller::call(f, args);
    EXPECT_EQ(global1, 120);
    EXPECT_EQ(global2, 130);
}