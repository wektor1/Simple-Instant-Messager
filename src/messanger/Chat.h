#pragma once
#include "ChatUIinterface.h"
#include "LogerInterface.h"
#include "MessReciverMangrInterface.h"
#include "MessSenderMangrInterface.h"
#include <functional>
#include <list>
#include <memory>
#include <mutex>
#include <string>

class Chat {
public:
  Chat(MessSenderMangrInterface *messSender,
       MessReciverMangrInterface *messReciver, LogerInterface *loger,
       ChatUIinterface *chatUI) noexcept;
  bool establishConnection();
  void openChat();

private:
  std::unique_ptr<MessSenderMangrInterface> m_messSender;
  std::unique_ptr<MessReciverMangrInterface> m_messReciver;
  std::unique_ptr<LogerInterface> m_loger;
  std::unique_ptr<ChatUIinterface> m_ui;
  MenuStatus m_menuStatus = MenuStatus::Menu;
  void optionSelect();
  std::string logsUpdate(const std::string &mess);
  void sendNewMessage(const std::string &mess);
  bool tryUntilTimeout(std::function<bool()> conn);
  void startReadingMessages();
  bool tryAcceptConnection();
  bool tryBeginConnection();
  void readUntilDisconnected();
  void chatMenuLoop();
  void messageCreation();
  void endChat();
  void drawUI();
};
