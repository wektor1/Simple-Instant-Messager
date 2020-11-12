#pragma once
#include <list>
#include <string>

class ChatUIinterface {
public:
  virtual ~ChatUIinterface() {}
  virtual void draw(const std::list<std::string> &logs) = 0;
};
