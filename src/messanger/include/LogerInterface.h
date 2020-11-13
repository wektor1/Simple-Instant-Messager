#pragma once
#include <list>
#include <string>

class LogerInterface {
public:
  virtual ~LogerInterface() {}
  virtual std::string makeSendLog(const std::string &mess) = 0;
  virtual void addLog(const std::string &mess) = 0;
  virtual std::list<std::string> &getLogs() = 0;
};
