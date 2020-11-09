#include "MessagesSenderManager.h"
#include <exception>
#include <string>

MessagesSenderManager::MessagesSenderManager(
    ClientInterface *messageSender,
    MessageHandlerInterface *messageHandler) noexcept
    : m_messageSender(std::move(messageSender)),
      m_messageHandler(std::move(messageHandler)) {}

void MessagesSenderManager::createNewMessage(const std::string mess) {
  std::lock_guard<std::mutex> lockQueue(messHandlerMutex);
  m_messageHandler->messageToQueue(mess);
}
bool MessagesSenderManager::beginConnection() {
  try {
    m_messageSender->connect();
  } catch (const std::exception &e) {
    return false;
  }
  return true;
}
