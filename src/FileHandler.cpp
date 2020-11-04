#include <FileHandler.h>

bool FileHandler::fileInQueue() const { return objectInQueue(); }

void FileHandler::fileToSend(const std::filesystem::path filePath) {
  objectToSend(filePath);
}
