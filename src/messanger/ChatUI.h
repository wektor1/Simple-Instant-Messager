#pragma once
#include <list>
#include <string>

class ChatUI {
public:
  ChatUI();
  void Draw(const std::list<std::string> &logs);

private:
  void ClearScrean();
  void prepareLogs(std::ostringstream &screen,
                   const std::list<std::string> &logs);
};
