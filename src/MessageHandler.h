#include "Handler_templ.h"
#include "Handler_templ.cpp"
#include <queue>
#include <string>

using StringHandler = Handler<std::string>;

class MessageHandler : public StringHandler {
public:
  bool messageInQueue() const;
  void messageToSend(const std::string mess);
};
