#pragma once
#include "ChatUI.h"
#include "MessReciverMangrInterface.h"
#include "MessSenderMangrInterface.h"
#include <list>
#include <memory>
#include <mutex>
#include <string>

class Chat {
public:
  Chat(MessSenderMangrInterface *messSender,
       MessReciverMangrInterface *messReciver,
       std::string name) noexcept;
  bool establishConnection();
  void startReadingMessages();
  void openChat();
  void endChat();

private:
  std::unique_ptr<MessSenderMangrInterface> m_messSender;
  std::unique_ptr<MessReciverMangrInterface> m_messReciver;
  std::list<std::string> m_lastLogs;
  ChatUI m_ui;
  std::mutex m_logsMutex;
  std::string m_name;
  void addLog(const std::string &newLog);
  void logsUpdate(const std::string log);
  void sendNewMessage(const std::string &mess);
  bool tryAcceptUntilTimeout();
  bool tryConnectUntilTimeout();
};
