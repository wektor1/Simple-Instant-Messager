#pragma once
#include <list>
#include <string>
#include <memory>

class LogerInterface {
public:
  virtual ~LogerInterface() = default;
  virtual std::string makeSendLog(const std::string &mess) = 0;
  virtual void addLog(const std::string &mess) = 0;
  virtual std::list<std::string> &getLogs() = 0;
};

std::unique_ptr<LogerInterface> makeLoger(const std::string &name);
