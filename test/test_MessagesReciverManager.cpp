#include "ComunicationExceptions.h"
#include "MessagesReciverManager.h"
#include "MockMessageHandlerInterface.h"
#include "MockServerInterface.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <stdexcept>

using ::testing::NiceMock;
using ::testing::Return;
using ::testing::StrictMock;

class MessagesReciverManagerTest : public ::testing::Test {
protected:
  void SetUp() override {
    servInt = new StrictMock<MockServerInterface>;
    msgHndl = new StrictMock<MockMessageHandlerInterface>;
  }
  void TearDown() override {}

  StrictMock<MockServerInterface> *servInt;
  StrictMock<MockMessageHandlerInterface> *msgHndl;
};

TEST_F(MessagesReciverManagerTest, AssertConnectionWithProperData) {
  EXPECT_CALL(*servInt, acceptConnection()).Times(1);

  MessagesReciverManager mgr(servInt, msgHndl);
  ASSERT_TRUE(mgr.acceptConnection());
}

TEST_F(MessagesReciverManagerTest, AssertConinuousReadThrowIfConnectionLost) {
  EXPECT_CALL(*servInt, read()).Times(1);

  MessagesReciverManager mgr(servInt, msgHndl);
  ASSERT_THROW(mgr.continuousBufferRead(), std::runtime_error);
}
