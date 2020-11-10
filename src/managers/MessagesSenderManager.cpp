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

bool MessagesSenderManager::beginConnection() {
  try {
    m_messageSender->connect();
  } catch (const std::exception &e) {
    return false;
  }
  std::lock_guard<std::mutex> lockValidator(m_messHandlerMutex);
  m_connectionValid = true;
  return true;
}

void MessagesSenderManager::endConnection() {
  std::lock_guard<std::mutex> lockQueue(m_messHandlerMutex);
  m_connectionValid = false;
  m_messageSender->disconnect();
}

void MessagesSenderManager::createNewMessage(const std::string mess) {
  std::lock_guard<std::mutex> lockQueue(m_messHandlerMutex);
  m_messageHandler->messageToQueue(mess);
}

void MessagesSenderManager::continuousMessageSending() {
  while (true) {
    m_messHandlerMutex.lock();
    if (m_messageHandler->messageInQueue() && m_connectionValid) {
      sendMessageInQueue();
    } else if (!m_connectionValid) {
      m_messHandlerMutex.unlock();
      break;
    }
    m_messHandlerMutex.unlock();
    std::this_thread::sleep_for(2s);
  }
}

void MessagesSenderManager::sendMessageInQueue() {
  m_messageSender->send(m_messageHandler->takeMessageFromQueue());
}
