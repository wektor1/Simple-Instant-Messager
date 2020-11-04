#include <queue>
#include <filesystem>
#include <Handler.h>

using PathHandler = Handler<std::filesystem::path>;
class FileHandler : public PathHandler {
public:
  bool filesInQueue() const;
};
