#include "ChatUI.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

ChatUI::ChatUI() {}

void ChatUI::Draw(const std::list<std::string> &logs) {
  ClearScrean();
  std::ostringstream screen(std::ios_base::ate);
  prepareLogs(screen, logs);
  screen << "Type your message:\n";
  std::cout << screen.str();
}

void ChatUI::prepareLogs(std::ostringstream &screen,
                         const std::list<std::string> &logs) {
  std::for_each(logs.crbegin(), logs.crend(),
                [&screen](auto &log) { screen << log << std::endl; });
}

void ChatUI::ClearScrean() { std::cout << std::string(100, '\n'); }
