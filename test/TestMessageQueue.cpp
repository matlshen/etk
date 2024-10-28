#include "etk/message_queue.h"
#include "etk/thread.h"
#include <gtest/gtest.h>

class MessageQueueTest : public ::testing::Test {
  protected:
    etk::message_queue<int, 2> mq;
    int global = 0;
};

void sendFunc(etk::message_queue<int, 2> &mq, int message) {
    etk::this_thread::msleep(1);
    mq.send(message);
}
void receiveFunc(etk::message_queue<int, 2> &mq, int &received_message) {
    received_message = mq.receive();
}
TEST_F(MessageQueueTest, TestSendAndReceive) {
    etk::thread t1(sendFunc, std::ref(mq), 42);
    etk::thread t2(receiveFunc, std::ref(mq), std::ref(global));

    t1.join();
    t2.join();

    EXPECT_EQ(global, 42);
}

TEST_F(MessageQueueTest, TestEmptyAndFull) {
    EXPECT_EQ(mq.empty(), true);
    EXPECT_EQ(mq.full(), false);

    mq.send(42);
    EXPECT_EQ(mq.empty(), false);
    EXPECT_EQ(mq.full(), false);

    mq.send(42);
    EXPECT_EQ(mq.empty(), false);
    EXPECT_EQ(mq.full(), true);

    mq.receive();
    EXPECT_EQ(mq.empty(), false);
    EXPECT_EQ(mq.full(), false);

    mq.receive();
    EXPECT_EQ(mq.empty(), true);
    EXPECT_EQ(mq.full(), false);
}

TEST_F(MessageQueueTest, TestTrySendReceive) {
    bool sent = mq.try_send(42);
    EXPECT_EQ(sent, true);

    sent = mq.try_send(42);
    EXPECT_EQ(sent, true);

    sent = mq.try_send(42);
    EXPECT_EQ(sent, false);

    int received_message;
    bool received = mq.try_receive(&received_message);
    EXPECT_EQ(received, true);
    EXPECT_EQ(received_message, 42);

    received = mq.try_receive(&received_message);
    EXPECT_EQ(received, true);
    EXPECT_EQ(received_message, 42);

    received = mq.try_receive(&received_message);
    EXPECT_EQ(received, false);
}

void receiveFuncMult(etk::message_queue<int, 2> &mq, int &received_message) {
    received_message = mq.receive();
    received_message += mq.receive();
    received_message += mq.receive();
    received_message += mq.receive();
}
TEST_F(MessageQueueTest, TestMultipleProducers) {
    std::array<etk::thread, 4> producers = {
        etk::thread(sendFunc, std::ref(mq), 1),
        etk::thread(sendFunc, std::ref(mq), 2),
        etk::thread(sendFunc, std::ref(mq), 3),
        etk::thread(sendFunc, std::ref(mq), 4)};
    etk::thread consumer(receiveFuncMult, std::ref(mq), std::ref(global));

    for (auto &t : producers) {
        t.join();
    }
    consumer.join();

    EXPECT_EQ(global, 10);
}