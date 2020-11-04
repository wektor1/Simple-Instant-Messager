#include "FileHandler.h"
#include <gtest/gtest.h>
#include <filesystem>

namespace fs = std::filesystem;

TEST(FileHandlerTest, AssertEmptyQueueAtStart){
  FileHandler fileHndlr;
  ASSERT_FALSE(fileHndlr.fileInQueue());
}

TEST(FileHandlerTest, AssertAddingFilesToQueue) {
  FileHandler fileHndlr;
  fileHndlr.fileToSend("/test/file.txt");
  ASSERT_TRUE(fileHndlr.fileInQueue());
}

TEST(FileHandlerTest, AssertProcessFirstToRemoveFirstFile) {
  FileHandler fileHndlr;
  fileHndlr.fileToSend("/test/file.txt");
  fileHndlr.processFirst();
  ASSERT_FALSE(fileHndlr.fileInQueue());
}

TEST(FileHandlerTest, AssertThrowIfProcessingEmptyQueue){
  FileHandler fileHndlr;
  ASSERT_THROW(fileHndlr.processFirst(), EmptyQueueException);
}

TEST(FileHandlerTest, AssertSameFileProcessing){
  FileHandler fileHndlr;
  fs::path file = "/test/file.txt";
  fileHndlr.fileToSend(file);
  auto processed_file = fileHndlr.processFirst();
  ASSERT_EQ(processed_file, file);
}
