#include "MessageHandler.h"
#include "MessagesReciverManager.h"
#include "MockServerInterface.h"
#include <future>
#include <chrono>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::Return;
using ::testing::AtLeast;
using namespace std::chrono_literals;

TEST(MessagesReciverManagerIntegration,
     AssertContinuousReadProperMessageQueuing) {
  MockServerInterface *servInt(new MockServerInterface);
  MessageHandler *msgHndl(new MessageHandler);

  EXPECT_CALL(*servInt, read())
      .Times(AtLeast(2))
      .WillOnce(Return("First"))
      .WillOnce(Return("Second"))
      .WillRepeatedly(Return("Default"));

  MessagesReciverManager mgr(servInt, msgHndl);
  mgr.acceptConnection();
  std::thread t1(&MessagesReciverManager::continuousBufferRead, &mgr);
  auto t2 = std::async(std::launch::async,
                       &MessagesReciverManager::giveLastMessage, &mgr);
  std::this_thread::sleep_for(3s);
  auto t3 = std::async(std::launch::async,
                       &MessagesReciverManager::giveLastMessage, &mgr);
  ASSERT_EQ(t2.get(), "First");
  ASSERT_EQ(t3.get(), "Second");
  mgr.endConnection();
  t1.join();
}
