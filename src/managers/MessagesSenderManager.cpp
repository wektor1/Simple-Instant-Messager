#include "MessagesSenderManager.h"
#include <exception>
#include <string>
#include <thread>

MessagesSenderManager::MessagesSenderManager(
    std::unique_ptr<ClientInterface> &&messageSender,
    std::unique_ptr<MessageHandlerInterface> &&messageHandler) noexcept
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
  m_conditionInQueue.notify_one();
}

void MessagesSenderManager::createNewMessage(const std::string mess) {
  std::lock_guard<std::mutex> lockQueue(m_messHandlerMutex);
  m_messageHandler->messageToQueue(mess);
  m_conditionInQueue.notify_one();
}

void MessagesSenderManager::continuousMessageSending() {
  std::unique_lock<std::mutex> queueLock(m_messHandlerMutex);
  while (true) {
    m_conditionInQueue.wait(queueLock);
    if (!m_connectionValid) {
      m_messHandlerMutex.unlock();
      m_messageSender->disconnect();
      break;
    }
    m_messHandlerMutex.unlock();
    sendMessageInQueue();
  }
}

void MessagesSenderManager::sendMessageInQueue() {
  m_messageSender->send(m_messageHandler->takeMessageFromQueue());
}

std::unique_ptr<MessSenderMangrInterface> makeMessSenderManager(
    std::unique_ptr<ClientInterface> &&messageSender,
    std::unique_ptr<MessageHandlerInterface> &&messageHandler) {
  return std::make_unique<MessagesSenderManager>(std::move(messageSender),
                                                    std::move(messageHandler));
}
