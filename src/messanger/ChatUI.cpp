#include "ChatUI.h"
#include <algorithm>
#include <iostream>
#include <mutex>
#include <sstream>
#include <string>

ChatUI::ChatUI() {}

void ChatUI::draw() {
  ClearScrean();
  std::ostringstream screen = fullChatBox();
  selectModule(screen);
  std::cout << screen.str();
}

void ChatUI::setStatus(const MenuStatus &status) {
  std::lock_guard<std::mutex> statusLock(m_statusMutex);
  m_status = status;
}

void ChatUI::setLastLogs(const std::list<std::string> &logs) {
  std::lock_guard<std::mutex> logsLock(m_logsMutex);
  m_lastLogs = logs;
}

std::ostringstream ChatUI::fullChatBox() {
  std::ostringstream screen(std::ios_base::ate);
  prepareBorder(screen);
  prepareLogs(screen);
  prepareBorder(screen);
  return screen;
}

void ChatUI::menuModule(std::ostringstream &screen) {
  screen << "1--Write new message\n"
         << "2--End chat\n"
         << "Type number:\n";
}

void ChatUI::selectModule(std::ostringstream &screen) {
  std::lock_guard<std::mutex> statusLock(m_statusMutex);
  switch (m_status) {
  case MenuStatus::Write:
    newMessageModule(screen);
    break;
  case MenuStatus::Menu:
    menuModule(screen);
    break;
  }
}

void ChatUI::newMessageModule(std::ostringstream &screen) {
  screen << "Type your message:\n";
}

void ChatUI::prepareLogs(std::ostringstream &screen) {
  std::lock_guard<std::mutex> logsLock(m_logsMutex);
  std::for_each(m_lastLogs.crbegin(), m_lastLogs.crend(),
                [&screen](auto &log) { screen << log << std::endl; });
}

void ChatUI::ClearScrean() { std::cout << std::string(100, '\n'); }

void ChatUI::prepareBorder(std::ostringstream &screen) {
  for (int i = 0; i < 40; i++) {
    screen << "-";
  }
  screen << std::endl;
}
