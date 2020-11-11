#include "Chat.h"
#include <algorithm>
#include <future>
#include <string>

Chat::Chat(MessSenderMangrInterface *messSender,
           MessReciverMangrInterface *messReciver) noexcept
    : m_messSender(std::move(messSender)),
      m_messReciver(std::move(messReciver)) {
  std::fill(m_lastLogs.begin(), m_lastLogs.end(), "");
}

bool Chat::establishConnection() {
  auto reciverConnected = std::async(
      std::launch::async, &MessReciverMangrInterface::acceptConnection,
      m_messReciver.get());
  auto senderConnected =
      std::async(std::launch::async, &MessSenderMangrInterface::beginConnection,
                 m_messSender.get());
  if (reciverConnected.get() && senderConnected.get())
    return true;
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
    addLog(newMessage);
    }
}

void Chat::endChat() {
  m_messReciver->endConnection();
  m_messSender->endConnection();
}
