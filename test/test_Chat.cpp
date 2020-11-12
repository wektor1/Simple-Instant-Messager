#include "Chat.h"
#include "ComunicationExceptions.h"
#include "MockMessReciverMangrInterface.h"
#include "MockMessSenderMangrInterface.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::Return;
using ::testing::StrictMock;
using ::testing::Throw;
using ::testing::AtLeast;

TEST(ChatTest, AssertConnectionReturnTrueAtSucces) {
  StrictMock<MockMessReciverMangrInterface> *messRec(
      new StrictMock<MockMessReciverMangrInterface>);
  StrictMock<MockMessSenderMangrInterface> *messSend(
      new StrictMock<MockMessSenderMangrInterface>);

  EXPECT_CALL(*messRec, acceptConnection()).Times(1).WillOnce(Return(true));
  EXPECT_CALL(*messSend, beginConnection()).Times(1).WillOnce(Return(true));

  Chat chat(messSend, messRec, "Test");
  ASSERT_TRUE(chat.establishConnection());
}

TEST(ChatTest, AssertConnectionReturnFalseAtFail) {
  StrictMock<MockMessReciverMangrInterface> *messRec(
      new StrictMock<MockMessReciverMangrInterface>);
  StrictMock<MockMessSenderMangrInterface> *messSend(
      new StrictMock<MockMessSenderMangrInterface>);

  EXPECT_CALL(*messRec, acceptConnection()).Times(AtLeast(1)).WillRepeatedly(Return(true));
  EXPECT_CALL(*messSend, beginConnection()).Times(AtLeast(1)).WillRepeatedly(Return(false));

  Chat chat(messSend, messRec, "Test");
  ASSERT_FALSE(chat.establishConnection());
}

TEST(ChatTest, AssertReadingUntilThrow) {
  StrictMock<MockMessReciverMangrInterface> *messRec(
      new StrictMock<MockMessReciverMangrInterface>);
  StrictMock<MockMessSenderMangrInterface> *messSend(
      new StrictMock<MockMessSenderMangrInterface>);

  EXPECT_CALL(*messRec, continuousBufferRead()).Times(1);
  EXPECT_CALL(*messRec, giveLastMessage())
      .Times(2)
      .WillOnce(Return("First"))
      .WillOnce(Throw(ConnectionLostException("Client ended conversation")));

  Chat chat(messSend, messRec, "Test");

  ASSERT_THROW(chat.startReadingMessages(), ConnectionLostException);
}
