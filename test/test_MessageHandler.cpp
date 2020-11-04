#include "MessageHandler.h"
#include <gtest/gtest.h>

TEST(MessageHandlerTest, AssertEmptyQueueAtStart) {
  MessageHandler messHndlr;
  ASSERT_FALSE(messHndlr.messageInQueue());
}
