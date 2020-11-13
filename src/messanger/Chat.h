#pragma once
#include "ChatInterface.h"
#include "ChatUIinterface.h"
#include "LogerInterface.h"
#include "MessReciverMangrInterface.h"
#include "MessSenderMangrInterface.h"
#include "TimerInterface.h"
#include <functional>
#include <list>
#include <memory>
#include <mutex>
#include <string>

class Chat : public ChatInterface {
public:
  Chat(MessSenderMangrInterface *messSender,
       MessReciverMangrInterface *messReciver, LogerInterface *loger,
       ChatUIinterface *chatUI, TimerInterface *timer) noexcept;
  bool establishConnection() override;
  void openChat() override;
  void startReadingMessages() override;
  void sendNewMessage(const std::string &mess) override;

private:
  std::unique_ptr<MessSenderMangrInterface> m_messSender;
  std::unique_ptr<MessReciverMangrInterface> m_messReciver;
  std::unique_ptr<LogerInterface> m_loger;
  std::unique_ptr<ChatUIinterface> m_ui;
  std::unique_ptr<TimerInterface> m_timer;
  MenuStatus m_menuStatus = MenuStatus::Menu;
  void logsUpdate();
  bool tryUntilTimeout(std::function<bool()> conn);
  bool tryAcceptConnection();
  bool tryBeginConnection();
  void readUntilDisconnected();
  void chatMenuLoop();
  void messageCreation();
  void optionSelect();
  void endChat();
  void drawUI();
};
