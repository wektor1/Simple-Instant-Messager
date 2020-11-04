#include "Handler.h"
#include <queue>
#include <string>

using StringHandler = Handler<std::string>;

class MessageHandler : public StringHandler {
public:
  bool messageInQueue() const;
  void messageToSend(const std::string mess);
};
