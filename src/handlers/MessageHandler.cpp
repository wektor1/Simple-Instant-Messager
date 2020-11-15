#include "MessageHandler.h"

bool MessageHandler::messageInQueue() const { return objectInQueue(); }

void MessageHandler::messageToQueue(const std::string mess) {
  objectToQueue(mess);
}

std::string MessageHandler::takeMessageFromQueue() { return processFirst(); }

std::unique_ptr<MessageHandlerInterface> makeMessageHandler(){
  return std::make_unique<MessageHandler>();
}
