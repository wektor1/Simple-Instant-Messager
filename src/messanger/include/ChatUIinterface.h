#pragma once
#include <list>
#include <string>
#include "enumMenuStatus.h"

class ChatUIinterface {
public:
  virtual ~ChatUIinterface() {}
  virtual void draw() = 0;
  virtual void setStatus(const MenuStatus &status) = 0;
  virtual void setLastLogs(const std::list<std::string> &logs) = 0;
};
