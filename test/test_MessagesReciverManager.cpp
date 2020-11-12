#include "ComunicationExceptions.h"
#include "MessagesReciverManager.h"
#include "MockMessageHandlerInterface.h"
#include "MockServerInterface.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <stdexcept>

using ::testing::Return;
using ::testing::StrictMock;

TEST(MessagesReciverManagerTest, AssertConnectionWithProperData) {
  StrictMock<MockServerInterface> *servInt(new StrictMock<MockServerInterface>);
  StrictMock<MockMessageHandlerInterface> *msgHndl(
      new StrictMock<MockMessageHandlerInterface>);

  EXPECT_CALL(*servInt, acceptConnection()).Times(1);

  MessagesReciverManager mgr(servInt, msgHndl);
  ASSERT_TRUE(mgr.acceptConnection());
}

TEST(MessagesReciverManagerTest, AssertGiveLastMessageWaitsForMessage) {
  StrictMock<MockServerInterface> *servInt(new StrictMock<MockServerInterface>);
  StrictMock<MockMessageHandlerInterface> *msgHndl(
      new StrictMock<MockMessageHandlerInterface>);

  EXPECT_CALL(*msgHndl, messageInQueue())
      .Times(3)
      .WillOnce(Return(false))
      .WillOnce(Return(false))
      .WillOnce(Return(true));
  EXPECT_CALL(*msgHndl, takeMessageFromQueue())
      .Times(1)
      .WillOnce(Return("mess"));
  EXPECT_CALL(*servInt, acceptConnection())
      .Times(1);

  MessagesReciverManager mgr(servInt, msgHndl);
  mgr.acceptConnection();
  ASSERT_EQ(mgr.giveLastMessage(), "mess");
}

TEST(MessagesReciverManagerTest, AssertConinuousReadThrowIfConnectionLost) {
  StrictMock<MockServerInterface> *servInt(new StrictMock<MockServerInterface>);
  StrictMock<MockMessageHandlerInterface> *msgHndl(
      new StrictMock<MockMessageHandlerInterface>);

  EXPECT_CALL(*servInt, read()).Times(1);
  MessagesReciverManager mgr(servInt, msgHndl);
  ASSERT_THROW(mgr.continuousBufferRead(), std::runtime_error);
}
