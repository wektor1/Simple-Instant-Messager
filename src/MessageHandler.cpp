#include "MessageHandler.h"
#include "HandlersExceptions.h"

bool MessageHandler::messageInQueue() const { return !m_messagesQueue.empty(); }

void MessageHandler::messageToSend(const std::string mess) {
  m_messagesQueue.push(mess);
}

std::string MessageHandler::processFirst() {
  if (!messageInQueue()) {
    throw EmptyQueueException("Empty message queue");
  }
  std::string mess = m_messagesQueue.front();
  m_messagesQueue.pop();
  return mess;
}
