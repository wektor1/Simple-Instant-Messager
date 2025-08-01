#pragma once
#include "ChatInterface.h"
#include "ChatUIinterface.h"
#include "LogerInterface.h"
#include "MessReciverMangrInterface.h"
#include "MessSenderMangrInterface.h"
#include <atomic>
#include <condition_variable>
#include <functional>
#include <list>
#include <memory>
#include <mutex>
#include <string>

class Chat : public ChatInterface {
public:
  Chat(std::unique_ptr<MessSenderMangrInterface> &&messSender,
       std::unique_ptr<MessReciverMangrInterface> &&messReciver,
       std::unique_ptr<LogerInterface> &&loger,
       std::unique_ptr<ChatUIinterface> &&chatUI) noexcept;
  bool establishConnection() override;
  void openChat() override;
  void startReadingMessages() override;
  void sendNewMessage(const std::string &mess) override;

private:
  std::unique_ptr<MessSenderMangrInterface> m_messSender;
  std::unique_ptr<MessReciverMangrInterface> m_messReciver;
  std::unique_ptr<LogerInterface> m_loger;
  std::unique_ptr<ChatUIinterface> m_ui;
  MenuStatus m_menuStatus = MenuStatus::Menu;
  std::mutex m_connectionMutex;
  std::condition_variable m_connectionCondition;
  std::atomic_bool connectionMade;
  void logsUpdate();
  void cancelConnection();
  void connectionLoop();
  void readUntilDisconnected();
  void chatMenuLoop();
  void messageCreation();
  void optionSelect();
  void endChat();
  void drawUI();
};
