#include "Chat.h"
#include "ComunicationExceptions.h"
#include "MockChatUIinterface.h"
#include "MockLogerInterface.h"
#include "MockMessReciverMangrInterface.h"
#include "MockMessSenderMangrInterface.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::AtLeast;
using ::testing::Return;
using ::testing::StrictMock;
using ::testing::Throw;

TEST(ChatTest, AssertConnectionReturnTrueAtSucces) {
  StrictMock<MockMessReciverMangrInterface> *messRec(
      new StrictMock<MockMessReciverMangrInterface>);
  StrictMock<MockMessSenderMangrInterface> *messSend(
      new StrictMock<MockMessSenderMangrInterface>);
  StrictMock<MockChatUIinterface> *chtUI(new StrictMock<MockChatUIinterface>);
  StrictMock<MockLogerInterface> *logr(new StrictMock<MockLogerInterface>);

  EXPECT_CALL(*messRec, acceptConnection()).Times(1).WillOnce(Return(true));
  EXPECT_CALL(*messSend, beginConnection()).Times(1).WillOnce(Return(true));

  Chat chat(messSend, messRec, logr, chtUI);
  ASSERT_TRUE(chat.establishConnection());
}

TEST(ChatTest, AssertConnectionReturnFalseAtFail) {
  StrictMock<MockMessReciverMangrInterface> *messRec(
      new StrictMock<MockMessReciverMangrInterface>);
  StrictMock<MockMessSenderMangrInterface> *messSend(
      new StrictMock<MockMessSenderMangrInterface>);
  StrictMock<MockChatUIinterface> *chtUI(new StrictMock<MockChatUIinterface>);
  StrictMock<MockLogerInterface> *logr(new StrictMock<MockLogerInterface>);

  EXPECT_CALL(*messRec, acceptConnection())
      .Times(AtLeast(1))
      .WillRepeatedly(Return(true));
  EXPECT_CALL(*messSend, beginConnection())
      .Times(AtLeast(1))
      .WillRepeatedly(Return(false));

  Chat chat(messSend, messRec, logr, chtUI);
  ASSERT_FALSE(chat.establishConnection());
}

TEST(ChatTest, AssertReadingUntilThrowFromDisconnect) {
  StrictMock<MockMessReciverMangrInterface> *messRec(
      new StrictMock<MockMessReciverMangrInterface>);
  StrictMock<MockMessSenderMangrInterface> *messSend(
      new StrictMock<MockMessSenderMangrInterface>);
  StrictMock<MockChatUIinterface> *chtUI(new StrictMock<MockChatUIinterface>);
  StrictMock<MockLogerInterface> *logr(new StrictMock<MockLogerInterface>);

  EXPECT_CALL(*messRec, endConnection()).Times(1);
  EXPECT_CALL(*messSend, endConnection()).Times(1);
  EXPECT_CALL(*messRec, continuousBufferRead())
      .Times(1)
      .WillOnce(Throw(ConnectionLostException("Client ended conversation")));
  EXPECT_CALL(*messRec, giveLastMessage())
      .Times(AtLeast(1))
      .WillRepeatedly(Return("First"));
  EXPECT_CALL(*logr, makeLog("First")).Times(AtLeast(1));

  Chat chat(messSend, messRec, logr, chtUI);

  ASSERT_THROW(chat.startReadingMessages(), std::runtime_error);
}
