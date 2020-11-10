#include "MessagesSenderManager.h"
#include "MockClientInterface.h"
#include "MockMessageHandlerInterface.h"
#include <chrono>
#include <future>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Return;
using namespace std::chrono_literals;

TEST(MessagesSenderManagerTest, AssertCorrectQueuingMessages) {
  MockClientInterface *cltInt(new MockClientInterface);
  MockMessageHandlerInterface *msgHndl(new MockMessageHandlerInterface);

  EXPECT_CALL(*msgHndl, messageToQueue(_)).Times(1);

  MessagesSenderManager mgr(cltInt, msgHndl);
  mgr.createNewMessage("New message");
}

TEST(MessagesSenderManagerTest, AssertConnectionEstablishedWithProperData) {
  MockClientInterface *cltInt(new MockClientInterface);
  MockMessageHandlerInterface *msgHndl(new MockMessageHandlerInterface);

  EXPECT_CALL(*cltInt, connect()).Times(1);

  MessagesSenderManager mgr(cltInt, msgHndl);
  ASSERT_TRUE(mgr.beginConnection());
}

TEST(MessagesSenderManagerTest, AssertContinuousMessagesSendingStops) {
  MockClientInterface *cltInt(new MockClientInterface);
  MockMessageHandlerInterface *msgHndl(new MockMessageHandlerInterface);

  EXPECT_CALL(*cltInt, send(_)).Times(2);
  EXPECT_CALL(*msgHndl, messageInQueue())
      .Times(AtLeast(2))
      .WillOnce(Return(true))
      .WillOnce(Return(true))
      .WillRepeatedly(Return(false));

  MessagesSenderManager mgr(cltInt, msgHndl);
  mgr.beginConnection();
  std::thread t1(&MessagesSenderManager::continuousMessageSending, &mgr);
  std::this_thread::sleep_for(3s);
  mgr.endConnection();
  t1.join();
}

TEST(MessagesSenderManagerTest, AssertAsyncWorkContinuousSendAndCreateNew) {
  MockClientInterface *cltInt(new MockClientInterface);
  MockMessageHandlerInterface *msgHndl(new MockMessageHandlerInterface);

  EXPECT_CALL(*cltInt, send(_)).Times(AtLeast(1));
  EXPECT_CALL(*msgHndl, messageInQueue())
      .Times(AtLeast(1))
      .WillRepeatedly(Return(true));

  MessagesSenderManager mgr(cltInt, msgHndl);
  mgr.beginConnection();
  std::thread t1(&MessagesSenderManager::continuousMessageSending, &mgr);
  auto t2 =
      std::async(std::launch::async, &MessagesSenderManager::createNewMessage,
                 &mgr, "Default");
  std::this_thread::sleep_for(1s);
  mgr.endConnection();
  t1.join();
}
