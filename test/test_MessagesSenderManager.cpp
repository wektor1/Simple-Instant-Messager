#include "MessagesSenderManager.h"
#include "MockClientInterface.cpp"
#include "MockMessageHandlerInterface.cpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::_;
using ::testing::Return;

TEST(MessagesSenderManagerTest, AssertCorrectQueuingMessages) {
  MockClientInterface *cltInt(new MockClientInterface);
  MockMessageHandlerInterface *msgHndl(new MockMessageHandlerInterface);

  EXPECT_CALL(*msgHndl, messageToQueue(_)).Times(1);

  MessagesSenderManager mgr(cltInt, msgHndl);
  mgr.createNewMessage("New message");
}

TEST(MessagesSenderManagerTest, AssertConnectionEstablishedWithProperData){
  MockClientInterface *cltInt(new MockClientInterface);
  MockMessageHandlerInterface *msgHndl(new MockMessageHandlerInterface);

  EXPECT_CALL(*cltInt, connect()).Times(1);

  MessagesSenderManager mgr(cltInt, msgHndl);
  ASSERT_TRUE(mgr.beginConnection());
}
