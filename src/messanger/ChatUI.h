#pragma once
#include "ChatUIinterface.h"
#include "enumMenuStatus.h"
#include <list>
#include <mutex>
#include <string>

class ChatUI : public ChatUIinterface {
public:
  ChatUI();
  void draw(const std::list<std::string> &logs) override;
  void setStatus(const MenuStatus &status);

  void menuModule(std::ostringstream &screen);

private:
  MenuStatus m_status = MenuStatus::Menu;
  std::mutex m_statusMutex;
  void ClearScrean();
  void prepareBorder(std::ostringstream &screen);
  void prepareLogs(std::ostringstream &screen,
                   const std::list<std::string> &logs);
  std::ostringstream fullChatBox(const std::list<std::string> &logs);
  void newMessageModule(std::ostringstream &screen);
  void selectModule(std::ostringstream &screen);
};
