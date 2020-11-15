#include "Chat.h"
#include "ComunicationExceptions.h"
#include "MockChatUIinterface.h"
#include "MockLogerInterface.h"
#include "MockMessReciverMangrInterface.h"
#include "MockMessSenderMangrInterface.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <list>
#include <string>

using ::testing::_;
using ::testing::AtLeast;
using ::testing::NiceMock;
using ::testing::Return;
using ::testing::ReturnRef;
using ::testing::StrictMock;
using ::testing::Throw;

class ChatTest : public ::testing::Test {
protected:
  void SetUp() override {
    messRec = new StrictMock<MockMessReciverMangrInterface>;
    messSend = new StrictMock<MockMessSenderMangrInterface>;
    chtUI = new StrictMock<MockChatUIinterface>;
    logr = new StrictMock<MockLogerInterface>;
  }
  void TearDown() override {}

  StrictMock<MockMessReciverMangrInterface> *messRec;
  StrictMock<MockMessSenderMangrInterface> *messSend;
  StrictMock<MockChatUIinterface> *chtUI;
  StrictMock<MockLogerInterface> *logr;
};

TEST_F(ChatTest, AssertConnectionReturnTrueAtSucces) {
  EXPECT_CALL(*messRec, acceptConnection()).Times(1).WillOnce(Return(true));
  EXPECT_CALL(*messSend, beginConnection()).Times(1).WillOnce(Return(true));

  Chat chat(messSend, messRec, logr, chtUI);
  ASSERT_TRUE(chat.establishConnection());
}

TEST_F(ChatTest, AssertReadingUntilThrowFromDisconnect) {
  EXPECT_CALL(*messRec, endConnection()).Times(1);
  EXPECT_CALL(*messSend, endConnection()).Times(1);
  EXPECT_CALL(*messRec, continuousBufferRead())
      .Times(1)
      .WillOnce(Throw(ConnectionLostException("Client ended conversation")));
  EXPECT_CALL(*messRec, giveLastMessage())
      .Times(AtLeast(1))
      .WillRepeatedly(Return("First"));
  EXPECT_CALL(*logr, addLog("First")).Times(AtLeast(1));

  Chat chat(messSend, messRec, logr, chtUI);

  ASSERT_THROW(chat.startReadingMessages(), std::runtime_error);
}

TEST_F(ChatTest, AssertSendNewMessLogsAndSends) {
  EXPECT_CALL(*logr, makeSendLog("Test mess"))
      .Times(1)
      .WillOnce(Return("Host 1: Test mess"));
  EXPECT_CALL(*messSend, createNewMessage("Host 1: Test mess")).Times(1);
  std::list<std::string> logs{"Host 1: Test mess"};
  EXPECT_CALL(*logr, getLogs()).Times(1).WillOnce(ReturnRef(logs));
  EXPECT_CALL(*chtUI, setLastLogs(_)).Times(1);
  EXPECT_CALL(*chtUI, draw()).Times(1);

  Chat chat(messSend, messRec, logr, chtUI);
  chat.sendNewMessage("Test mess");
}
