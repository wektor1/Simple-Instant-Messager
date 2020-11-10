#include "MessageHandler.h"

bool MessageHandler::messageInQueue() const { return objectInQueue(); }

void MessageHandler::messageToQueue(const std::string mess) {
  objectToQueue(mess);
}

std::string MessageHandler::takeMessageFromQueue() { return processFirst(); }
