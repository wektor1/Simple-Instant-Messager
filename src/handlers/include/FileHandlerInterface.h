#pragma once

#include <filesystem>

class FileHandlerInterface {
public:
  virtual ~FileHandlerInterface() = default;
  virtual bool fileInQueue() const = 0;
  virtual void fileToQueue(const std::filesystem::path) = 0;
  virtual std::filesystem::path fileToSend() = 0;
};
