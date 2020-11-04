#include "MessageHandler.h"
//#include "HandlersExceptions.h"
#include <gtest/gtest.h>
#include <string>

TEST(MessageHandlerTest, AssertEmptyQueueAtStart) {
  MessageHandler messHndlr;
  ASSERT_FALSE(messHndlr.messageInQueue());
}

TEST(MessageHandlerTest, AssertAddingMessagesToQueue) {
  MessageHandler messHndlr;
  messHndlr.messageToSend("New Mess");
  ASSERT_TRUE(messHndlr.messageInQueue());
}

TEST(MessageHandlerTest, AssertProcessFirstToRemoveFirstMess) {
  MessageHandler messHndlr;
  messHndlr.messageToSend("New Mess");
  messHndlr.processFirst();
  ASSERT_FALSE(messHndlr.messageInQueue());
}

TEST(MessageHandlerTest, AssertThrowIfProcessingEmptyQueue){
  MessageHandler messHndlr;
  ASSERT_THROW(messHndlr.processFirst(), EmptyQueueException);
}

TEST(MessageHandlerTest, AssertSameMessageProcessing){
  MessageHandler messHndlr;
  std::string mess = "New mess";
  messHndlr.messageToSend(mess);
  auto processed_mess = messHndlr.processFirst();
  ASSERT_EQ(processed_mess, mess);
}
