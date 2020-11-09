#include "HandlersExceptions.h"
#include "MessageHandler.h"
#include <gtest/gtest.h>
#include <string>

TEST(MessageHandlerTest, AssertEmptyQueueAtStart) {
  MessageHandler messHndlr;
  ASSERT_FALSE(messHndlr.messageInQueue());
}

TEST(MessageHandlerTest, AssertAddingMessagesToQueue) {
  MessageHandler messHndlr;
  messHndlr.messageToQueue("New Mess");
  ASSERT_TRUE(messHndlr.messageInQueue());
}

TEST(MessageHandlerTest, AssertProcessFirstToRemoveFirstMess) {
  MessageHandler messHndlr;
  messHndlr.messageToQueue("New Mess");
  messHndlr.messageToSend();
  ASSERT_FALSE(messHndlr.messageInQueue());
}

TEST(MessageHandlerTest, AssertThrowIfProcessingEmptyQueue) {
  MessageHandler messHndlr;
  ASSERT_THROW(messHndlr.messageToSend(), EmptyQueueException);
}

TEST(MessageHandlerTest, AssertSameMessageProcessing) {
  MessageHandler messHndlr;
  std::string mess = "New mess";
  messHndlr.messageToQueue(mess);
  auto processed_mess = messHndlr.messageToSend();
  ASSERT_EQ(processed_mess, mess);
}
