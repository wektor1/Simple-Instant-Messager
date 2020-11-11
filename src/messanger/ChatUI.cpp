#include "ChatUI.h"
#include <iostream>
#include <string>

ChatUI::ChatUI() {}

void ChatUI::Draw() {
  ClearScrean();
}

void ChatUI::ClearScrean() {
  std::cout<< std::string(100, '\n');
}
