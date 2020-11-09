#include "FileHandler.h"
#include "HandlersExceptions.h"
#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>

namespace fs = std::filesystem;

class FileHandlerTest : public ::testing::Test {
protected:
  void SetUp() override {
    std::ofstream testFile(pathToTestFile);
    testFile.close();
  }

  void TearDown() override { fs::remove(pathToTestFile); }

  fs::path pathToTestFile = "../testfile.txt";
};

TEST_F(FileHandlerTest, AssertEmptyQueueAtStart) {
  FileHandler fileHndlr;
  ASSERT_FALSE(fileHndlr.fileInQueue());
}

TEST_F(FileHandlerTest, AssertAddingFilesToQueue) {
  FileHandler fileHndlr;
  fileHndlr.fileToQueue("../testfile.txt");
  ASSERT_TRUE(fileHndlr.fileInQueue());
}

TEST_F(FileHandlerTest, AssertThrowIfFilesNotExist) {
  FileHandler fileHndlr;
  ASSERT_THROW(fileHndlr.fileToQueue("../testfile1.txt"), FileNotFoundException);
}

TEST_F(FileHandlerTest, AssertProcessFirstToRemoveFirstFile) {
  FileHandler fileHndlr;
  fileHndlr.fileToQueue("../testfile.txt");
  fileHndlr.fileToSend();
  ASSERT_FALSE(fileHndlr.fileInQueue());
}

TEST_F(FileHandlerTest, AssertThrowIfProcessingEmptyQueue) {
  FileHandler fileHndlr;
  ASSERT_THROW(fileHndlr.fileToSend(), EmptyQueueException);
}

TEST_F(FileHandlerTest, AssertSameFileProcessing) {
  FileHandler fileHndlr;
  fs::path file = "../testfile.txt";
  fileHndlr.fileToQueue(file);
  auto processed_file = fileHndlr.fileToSend();
  ASSERT_EQ(processed_file, file);
}
