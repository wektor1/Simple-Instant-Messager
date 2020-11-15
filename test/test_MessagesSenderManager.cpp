#include "MessagesSenderManager.h"
#include "MockClientInterface.h"
#include "MockMessageHandlerInterface.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::AtLeast;
using ::testing::NiceMock;
using ::testing::Return;
using ::testing::StrictMock;

class MessagesSenderManagerTest : public ::testing::Test {
protected:
  void SetUp() override {
    cltInt = new StrictMock<MockClientInterface>;
    msgHndl = new StrictMock<MockMessageHandlerInterface>;
  }
  void TearDown() override {}

  StrictMock<MockClientInterface> *cltInt;
  StrictMock<MockMessageHandlerInterface> *msgHndl;
};

TEST_F(MessagesSenderManagerTest, AssertCorrectQueuingMessages) {
  EXPECT_CALL(*msgHndl, messageToQueue("New message")).Times(1);

  MessagesSenderManager mgr(cltInt, msgHndl);
  mgr.createNewMessage("New message");
}

TEST_F(MessagesSenderManagerTest, AssertCorrectConnecion) {
  EXPECT_CALL(*cltInt, connect()).Times(1);

  MessagesSenderManager mgr(cltInt, msgHndl);
  ASSERT_TRUE(mgr.beginConnection());
}
