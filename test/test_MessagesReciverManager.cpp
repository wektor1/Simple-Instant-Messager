#include "ComunicationExceptions.h"
#include "MessagesReciverManager.h"
#include "MockMessageHandlerInterface.h"
#include "MockServerInterface.h"
#include <future>
#include <chrono>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::_;
using ::testing::Return;
using ::testing::AtLeast;
using namespace std::chrono_literals;

void threadTryCatch() {}

TEST(MessagesReciverManagerTest, AssertConnectionWithProperData) {
  MockServerInterface *servInt(new MockServerInterface);
  MockMessageHandlerInterface *msgHndl(new MockMessageHandlerInterface);

  EXPECT_CALL(*servInt, acceptConnection()).Times(1);

  MessagesReciverManager mgr(servInt, msgHndl);
  ASSERT_TRUE(mgr.acceptConnection());
}

TEST(MessagesReciverManagerTest, AssertContinuousReadStopsAtEndConnection) {
  MockServerInterface *servInt(new MockServerInterface);
  MockMessageHandlerInterface *msgHndl(new MockMessageHandlerInterface);

  EXPECT_CALL(*servInt, read())
      .Times(AtLeast(2))
      .WillOnce(Return("First"))
      .WillOnce(Return("Second"))
      .WillRepeatedly(Return("Default"));
  EXPECT_CALL(*msgHndl, messageToQueue("Second"));
  EXPECT_CALL(*msgHndl, messageToQueue("First"));

  MessagesReciverManager mgr(servInt, msgHndl);
  mgr.acceptConnection();
  std::thread t1(&MessagesReciverManager::continuousBufferRead, &mgr);
  std::this_thread::sleep_for(3s);
  mgr.endConnection();
  t1.join();
}

TEST(MessagesReciverManagerTest, AssertReadAndGiveAsyncWork) {
  MockServerInterface *servInt(new MockServerInterface);
  MockMessageHandlerInterface *msgHndl(new MockMessageHandlerInterface);

  EXPECT_CALL(*servInt, read())
      .Times(AtLeast(1))
      .WillRepeatedly(Return("Default"));
  EXPECT_CALL(*msgHndl, messageInQueue())
      .Times(AtLeast(1))
      .WillRepeatedly(Return(true));
  EXPECT_CALL(*msgHndl, takeMessageFromQueue())
      .Times(AtLeast(1))
      .WillRepeatedly(Return("Default"));
  MessagesReciverManager mgr(servInt, msgHndl);
  mgr.acceptConnection();
  std::thread t1(&MessagesReciverManager::continuousBufferRead, &mgr);
  auto t2 = std::async(std::launch::async, &MessagesReciverManager::giveLastMessage, &mgr);
  std::this_thread::sleep_for(1s);
  mgr.endConnection();
  t1.join();
  ASSERT_EQ(t2.get(), "Default");
}
