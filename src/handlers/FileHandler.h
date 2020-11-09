#include "Handler_templ.h"
#include "Handler_templ.cpp"
#include "FileHandlerInterface.h"
#include <filesystem>
#include <queue>

using PathHandler = Handler<std::filesystem::path>;
class FileHandler : public FileHandlerInterface, PathHandler {
public:
  bool fileInQueue() const override;
  void fileToQueue(const std::filesystem::path) override;
  std::filesystem::path fileToSend() override;
};
