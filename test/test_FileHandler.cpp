#include "FileHandler.h"
#include <gtest/gtest.h>

TEST(FileHandlerTest, AssertEmptyQueueAtStart){
  FileHandler fileHndlr;
  ASSERT_FALSE(fileHndlr.filesInQueue());
}
