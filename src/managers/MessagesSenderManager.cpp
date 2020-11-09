#include "MessagesSenderManager.h"
#include <chrono>
#include <exception>
#include <string>
#include <thread>

using namespace std::chrono_literals;

MessagesSenderManager::MessagesSenderManager(
    ClientInterface *messageSender,
    MessageHandlerInterface *messageHandler) noexcept
    : m_messageSender(std::move(messageSender)),
      m_messageHandler(std::move(messageHandler)), m_connectionValid(false) {}

void MessagesSenderManager::createNewMessage(const std::string mess) {
  std::lock_guard<std::mutex> lockQueue(m_messHandlerMutex);
  m_messageHandler->messageToQueue(mess);
}
bool MessagesSenderManager::beginConnection() {
  try {
    m_messageSender->connect();
  } catch (const std::exception &e) {
    return false;
  }
  m_connectionValid = true;
  return true;
}

void MessagesSenderManager::endConnection() {
  std::lock_guard<std::mutex> lockQueue(m_messHandlerMutex);
  m_connectionValid = false;
}

void MessagesSenderManager::continuousMessageSending() {
  while (true) {
    m_messHandlerMutex.lock();
    if (m_messageHandler->messageInQueue() && m_connectionValid) {
      m_messageSender->send(m_messageHandler->messageToSend());
    } else if (!m_connectionValid) {
      m_messHandlerMutex.unlock();
      break;
    }
    m_messHandlerMutex.unlock();
    std::this_thread::sleep_for(2s);
  }
}
