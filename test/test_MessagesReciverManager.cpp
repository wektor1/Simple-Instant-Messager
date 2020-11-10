#include "MessagesReciverManager.h"
#include "ComunicationExceptions.h"
#include "mocks/MockMessageHandlerInterface.h"
#include "mocks/MockServerInterface.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <future>

using ::testing::Return;
using ::testing::Throw;

TEST(MessagesReciverManager, AssertConnectionWithProperData) {
  MockServerInterface *servInt(new MockServerInterface);
  MockMessageHandlerInterface *msgHndl(new MockMessageHandlerInterface);

  EXPECT_CALL(*servInt, acceptConnection()).Times(1);

  MessagesReciverManager mgr(servInt, msgHndl);
  ASSERT_TRUE(mgr.acceptConnection());
}

TEST(MessagesReciverManager, AssertContinuousReadStopsAtException) {
  MockServerInterface *servInt(new MockServerInterface);
  MockMessageHandlerInterface *msgHndl(new MockMessageHandlerInterface);

  EXPECT_CALL(*servInt, read())
      .Times(3)
      .WillOnce(Return("First"))
      .WillOnce(Return("Second"))
      .WillRepeatedly(Throw(ConnectionLostException("Client ended conversation")));
  EXPECT_CALL(*msgHndl, messageToQueue("Second"));
  EXPECT_CALL(*msgHndl, messageToQueue("First"));

  MessagesReciverManager mgr(servInt, msgHndl);
  std::thread t1(&MessagesReciverManager::continuousBufferRead, &mgr);
  t1.join();
}
