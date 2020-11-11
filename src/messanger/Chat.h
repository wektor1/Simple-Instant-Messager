#pragma once
#include "MessReciverMangrInterface.h"
#include "MessSenderMangrInterface.h"
#include <list>
#include <memory>
#include <string>

class Chat {
public:
  Chat(MessSenderMangrInterface *messSender,
       MessReciverMangrInterface *messReciver) noexcept;
  bool establishConnection();
  void startReadingMessages();
  void endChat();

private:
  std::unique_ptr<MessSenderMangrInterface> m_messSender;
  std::unique_ptr<MessReciverMangrInterface> m_messReciver;
  std::list<std::string> m_lastLogs;
  void addLog(const std::string &newLog);
};
