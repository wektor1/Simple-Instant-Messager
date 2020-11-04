#include "MessageHandler.h"

bool MessageHandler::messageInQueue() const { return objectInQueue(); }

void MessageHandler::messageToSend(const std::string mess) {
  objectToSend(mess);
}
