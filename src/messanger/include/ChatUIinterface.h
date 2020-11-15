#pragma once
#include <list>
#include <string>
#include "enumMenuStatus.h"
#include <memory>

class ChatUIinterface {
public:
  virtual ~ChatUIinterface() = default;
  virtual void draw() = 0;
  virtual void setStatus(const MenuStatus &status) = 0;
  virtual void setLastLogs(const std::list<std::string> &logs) = 0;
};

std::unique_ptr<ChatUIinterface> makeChatUI();
