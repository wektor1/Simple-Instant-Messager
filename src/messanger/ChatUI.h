#pragma once
#include "ChatUIinterface.h"
#include "enumMenuStatus.h"
#include <list>
#include <mutex>
#include <string>

class ChatUI : public ChatUIinterface {
public:
  ChatUI();
  void draw() override;
  void setStatus(const MenuStatus &status) override;
  void setLastLogs(const std::list<std::string> &logs) override;

private:
  std::list<std::string> m_lastLogs;
  MenuStatus m_status = MenuStatus::Menu;
  std::mutex m_logsMutex;
  std::mutex m_statusMutex;
  void ClearScrean();
  void prepareBorder(std::ostringstream &screen);
  void prepareLogs(std::ostringstream &screen);
  void menuModule(std::ostringstream &screen);
  std::ostringstream fullChatBox();
  void newMessageModule(std::ostringstream &screen);
  void selectModule(std::ostringstream &screen);
};
