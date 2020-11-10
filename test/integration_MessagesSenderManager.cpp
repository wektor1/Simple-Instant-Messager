#include "MessageHandler.h"
#include "MessagesSenderManager.h"
#include "mocks/MockClientInterface.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <chrono>
#include <future>

using namespace std::chrono_literals;

TEST(MessagesSenderManagerIntegration, AssertCorrectQueuingMessages) {
  MockClientInterface *cltInt(new MockClientInterface);
  MessageHandler *msgHndl(new MessageHandler);

  EXPECT_CALL(*cltInt, send("Second"))
      .Times(1);
  EXPECT_CALL(*cltInt, send("New message"))
      .Times(1);

  MessagesSenderManager mgr(cltInt, msgHndl);
  mgr.beginConnection();
  std::thread t1(&MessagesSenderManager::continuousMessageSending, &mgr);
  mgr.createNewMessage("New message");
  mgr.createNewMessage("Second");
  std::this_thread::sleep_for(3s);
  mgr.endConnection();
  t1.join();
}

TEST(MessagesSenderManagerIntegration, AssertAsyncWorkContinuousSendAndCreateNew) {
  MockClientInterface *cltInt(new MockClientInterface);
  MessageHandler *msgHndl(new MessageHandler);

  EXPECT_CALL(*cltInt, send("Second")).Times(1);
  EXPECT_CALL(*cltInt, send("First")).Times(1);

  MessagesSenderManager mgr(cltInt, msgHndl);
  mgr.beginConnection();
  std::thread t1(&MessagesSenderManager::continuousMessageSending, &mgr);
  auto t2 =
      std::async(std::launch::async, &MessagesSenderManager::createNewMessage,
                 &mgr, "First");
  auto t3 =
      std::async(std::launch::async, &MessagesSenderManager::createNewMessage,
                 &mgr, "Second");
  std::this_thread::sleep_for(5s);
  mgr.endConnection();
  t1.join();
}

