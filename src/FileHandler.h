#include <Handler.h>
#include <filesystem>
#include <queue>

using PathHandler = Handler<std::filesystem::path>;
class FileHandler : public PathHandler {
public:
  bool fileInQueue() const;
  void fileToSend(const std::filesystem::path);
};
