#include "MessagesReciverManager.h"
#include <chrono>
#include <exception>
#include <thread>

using namespace std::chrono_literals;

MessagesReciverManager::MessagesReciverManager(
    ServerInterface *messageReciver,
    MessageHandlerInterface *messageHandler) noexcept
    : m_messageReciver(std::move(messageReciver)),
      m_messageHandler(std::move(messageHandler)) {}

bool MessagesReciverManager::acceptConnection() {
  try {
    m_messageReciver->acceptConnection();
  } catch (const std::exception &e) {
    return false;
  }
  return true;
}

void MessagesReciverManager::continuousBufferRead() {
  std::string mess;
  while (true) {
    try {
      mess = m_messageReciver->read();
    } catch (std::exception &e) {
      break;
    }
    m_messHandlerMutex.lock();
    m_messageHandler->messageToQueue(mess);
    m_messHandlerMutex.unlock();
    std::this_thread::sleep_for(2s);
  }
}
