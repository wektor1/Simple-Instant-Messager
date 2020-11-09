#include "FileHandler.h"
#include "HandlersExceptions.h"
#include <filesystem>

namespace fs = std::filesystem;

bool FileHandler::fileInQueue() const { return objectInQueue(); }

void FileHandler::fileToQueue(const std::filesystem::path filePath) {
  fs::exists(filePath)
      ? objectToQueue(filePath)
      : throw FileNotFoundException("Filepath doesn't include file");
}

std::filesystem::path FileHandler::fileToSend() { return processFirst(); }
