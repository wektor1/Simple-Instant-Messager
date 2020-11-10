#include "MessagesSenderManager.h"
#include "MockClientInterface.h"
#include "MockMessageHandlerInterface.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::AtLeast;
using ::testing::Return;
using ::testing::StrictMock;

TEST(MessagesSenderManagerTest, AssertCorrectQueuingMessages) {
  StrictMock<MockClientInterface> *cltInt(new StrictMock<MockClientInterface>);
  StrictMock<MockMessageHandlerInterface> *msgHndl(
      new StrictMock<MockMessageHandlerInterface>);

  EXPECT_CALL(*msgHndl, messageToQueue("New message")).Times(1);

  MessagesSenderManager mgr(cltInt, msgHndl);
  mgr.createNewMessage("New message");
}

TEST(MessagesSenderManagerTest, AssertCorrectConnecion) {
  StrictMock<MockClientInterface> *cltInt(new StrictMock<MockClientInterface>);
  StrictMock<MockMessageHandlerInterface> *msgHndl(
      new StrictMock<MockMessageHandlerInterface>);

  EXPECT_CALL(*cltInt, connect()).Times(1);

  MessagesSenderManager mgr(cltInt, msgHndl);
  ASSERT_TRUE(mgr.beginConnection());
}

TEST(MessagesSenderManagerTest, AssertCorrectDisconnect) {
  StrictMock<MockClientInterface> *cltInt(new StrictMock<MockClientInterface>);
  StrictMock<MockMessageHandlerInterface> *msgHndl(
      new StrictMock<MockMessageHandlerInterface>);

  EXPECT_CALL(*cltInt, disconnect()).Times(1);

  MessagesSenderManager mgr(cltInt, msgHndl);
  mgr.endConnection();
}

TEST(MessagesSenderManagerTest,
     AssertConinuousSendingInstantBreakWithoutConnection) {
  StrictMock<MockClientInterface> *cltInt(new StrictMock<MockClientInterface>);
  StrictMock<MockMessageHandlerInterface> *msgHndl(
      new StrictMock<MockMessageHandlerInterface>);

  EXPECT_CALL(*msgHndl, messageInQueue()).Times(1);
  MessagesSenderManager mgr(cltInt, msgHndl);
  mgr.continuousMessageSending();
}
