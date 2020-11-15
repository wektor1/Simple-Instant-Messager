#include "MessagesReciverManager.h"
#include <exception>
#include <thread>

MessagesReciverManager::MessagesReciverManager(
    std::unique_ptr<ServerInterface> &&messageReciver,
    std::unique_ptr<MessageHandlerInterface> &&messageHandler) noexcept
    : m_messageReciver(std::move(messageReciver)),
      m_messageHandler(std::move(messageHandler)), m_connectionValid(false) {}

bool MessagesReciverManager::acceptConnection() {
  try {
    m_messageReciver->acceptConnection();
  } catch (const std::exception &e) {
    return false;
  }
  std::lock_guard<std::mutex> lockValidator(m_messHandlerMutex);
  m_connectionValid = true;
  return true;
}

void MessagesReciverManager::endConnection() {
  std::lock_guard<std::mutex> lockQueue(m_messHandlerMutex);
  m_connectionValid = false;
  m_conditionInQueue.notify_one();
}

std::string MessagesReciverManager::giveLastMessage() {
  std::unique_lock<std::mutex> queueLock(m_messHandlerMutex);
  m_conditionInQueue.wait(queueLock);
  if (!m_connectionValid) {
    queueLock.unlock();
    throw std::runtime_error("Ended reading messages");
  }
  queueLock.unlock();
  std::string temp = m_messageHandler->takeMessageFromQueue();
  return temp;
}

void MessagesReciverManager::continuousBufferRead() {
  std::string mess;
  while (true) {
    mess = m_messageReciver->read();
    m_messHandlerMutex.lock();
    if (!m_connectionValid) {
      m_messHandlerMutex.unlock();
      throw std::runtime_error("Ended buffer reading messages");
    }
    m_messageHandler->messageToQueue(mess);
    m_messHandlerMutex.unlock();
    m_conditionInQueue.notify_one();
  }
}

std::unique_ptr<MessReciverMangrInterface> makeMessReciverManager(
    std::unique_ptr<ServerInterface> &&messageReciver,
    std::unique_ptr<MessageHandlerInterface> &&messageHandler) {
  return std::make_unique<MessagesReciverManager>(std::move(messageReciver),
                                                  std::move(messageHandler));
}
