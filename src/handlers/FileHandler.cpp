#include "HandlersExceptions.h"
#include "FileHandler.h"
#include <filesystem>

namespace fs = std::filesystem;

bool FileHandler::fileInQueue() const { return objectInQueue(); }

void FileHandler::fileToSend(const std::filesystem::path filePath) {
  fs::exists(filePath) ? objectToSend(filePath)
                       : throw FileNotFound("Filepath doesn't include file");
}
