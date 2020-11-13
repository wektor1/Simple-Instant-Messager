#include "MessagesReciverManager.h"
#include <chrono>
#include <exception>
#include <iostream>
#include <thread>

using namespace std::chrono_literals;

MessagesReciverManager::MessagesReciverManager(
    ServerInterface *messageReciver,
    MessageHandlerInterface *messageHandler, TimerInterface *timer) noexcept
    : m_messageReciver(std::move(messageReciver)),
      m_messageHandler(std::move(messageHandler)), m_connectionValid(false),
      m_timer(std::move(timer)) {}

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
    if (m_messageHandler->messageInQueue()) {
      std::string temp = m_messageHandler->takeMessageFromQueue();
      m_messHandlerMutex.unlock();
      return temp;
    } else if (!m_connectionValid) {
      m_messHandlerMutex.unlock();
      throw std::runtime_error("Reading connection lost");
    }
    m_messHandlerMutex.unlock();
    m_timer->sleep(2s);
  }
}

void MessagesReciverManager::continuousBufferRead() {
  std::string mess;
  while (true) {
    mess = m_messageReciver->read();
    m_messHandlerMutex.lock();
    if (!m_connectionValid) {
      m_messHandlerMutex.unlock();
      throw std::runtime_error("Ended reading messages");
    }
    m_messageHandler->messageToQueue(mess);
    m_messHandlerMutex.unlock();
    std::this_thread::sleep_for(2s);
  }
}
