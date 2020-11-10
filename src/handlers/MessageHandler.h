#include "Handler_templ.h"
#include "Handler_templ.cpp"
#include "MessageHandlerInterface.h"
#include <queue>
#include <string>

using StringHandler = Handler<std::string>;

class MessageHandler : public MessageHandlerInterface, StringHandler {
public:
  bool messageInQueue() const override;
  void messageToQueue(const std::string mess) override;
  std::string takeMessageFromQueue() override;
};
