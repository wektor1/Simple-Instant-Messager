#include "Chat.h"
#include <algorithm>
#include <chrono>
#include <future>
#include <iostream>
#include <string>

using namespace std::chrono_literals;

Chat::Chat(MessSenderMangrInterface *messSender,
           MessReciverMangrInterface *messReciver) noexcept
    : m_messSender(std::move(messSender)),
      m_messReciver(std::move(messReciver)) {
  std::fill(m_lastLogs.begin(), m_lastLogs.end(), "");
}

bool Chat::establishConnection() {
  auto reciverConnected =
      std::async(std::launch::async, &Chat::tryAcceptUntilTimeout, this);
  auto senderConnected =
      std::async(std::launch::async, &Chat::tryConnectUntilTimeout, this);
  if (reciverConnected.get() && senderConnected.get())
    return true;
  return false;
}

bool Chat::tryAcceptUntilTimeout() {
  auto start_time = std::chrono::system_clock::now();
  auto current_time = start_time;
  while (current_time < start_time + 10s) {
    auto result = m_messReciver->acceptConnection();
    if (result)
      return true;
    current_time = std::chrono::system_clock::now();
  }
  return false;
}

bool Chat::tryConnectUntilTimeout() {
  auto start_time = std::chrono::system_clock::now();
  auto current_time = start_time;
  while (current_time < start_time + 10s) {
    auto result = m_messSender->beginConnection();
    if (result)
      return true;
    current_time = std::chrono::system_clock::now();
  }
  return false;
}

void Chat::addLog(const std::string &newLog) {
  if (m_lastLogs.size() == 10)
    m_lastLogs.pop_back();
  m_lastLogs.push_front(newLog);
}

void Chat::startReadingMessages() {
  auto readBuff = std::async(std::launch::async,
                             &MessReciverMangrInterface::continuousBufferRead,
                             m_messReciver.get());
  while (true) {
    std::string newMessage = m_messReciver->giveLastMessage();
    m_logsMutex.lock();
    logsUpdate(newMessage);
    m_logsMutex.unlock();
  }
}

void Chat::logsUpdate(const std::string log) {
  addLog(log);
  m_ui.Draw(m_lastLogs);
}

void Chat::sendNewMessage(const std::string &mess) {
  m_logsMutex.lock();
  logsUpdate(mess);
  m_logsMutex.unlock();
  m_messSender->createNewMessage(mess);
}

void Chat::openChat() {
  auto readingRecived =
      std::async(std::launch::async, &Chat::startReadingMessages, this);
  auto sendMess = std::async(
      std::launch::async, &MessSenderMangrInterface::continuousMessageSending,
      m_messSender.get());
  std::string userMessage;
  while (true) {
    std::getline(std::cin, userMessage);
    sendNewMessage(userMessage);
  }
}

void Chat::endChat() {
  m_messReciver->endConnection();
  m_messSender->endConnection();
}
