#include "MessagesReciverManager.h"
#include <chrono>
#include <exception>
#include <thread>

using namespace std::chrono_literals;

MessagesReciverManager::MessagesReciverManager(
    ServerInterface *messageReciver,
    MessageHandlerInterface *messageHandler) noexcept
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
}

std::string MessagesReciverManager::giveLastMessage() {
  while (true) {
    m_messHandlerMutex.lock();
    if(m_messageHandler->messageInQueue()){
      std::string temp = m_messageHandler->takeMessageFromQueue();
      m_messHandlerMutex.unlock();
      return temp;
    }
    m_messHandlerMutex.unlock();
    std::this_thread::sleep_for(2s);
  }
}

void MessagesReciverManager::continuousBufferRead() {
  std::string mess;
  while (true) {
    mess = m_messageReciver->read();
    m_messHandlerMutex.lock();
    if (!m_connectionValid) {
      m_messHandlerMutex.unlock();
      break;
    }
    m_messageHandler->messageToQueue(mess);
    m_messHandlerMutex.unlock();
    std::this_thread::sleep_for(2s);
  }
}
