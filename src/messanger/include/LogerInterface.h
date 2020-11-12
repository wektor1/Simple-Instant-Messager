#pragma once
#include <string>
#include <list>

class LogerInterface {
public:
  virtual ~LogerInterface() {}
  virtual std::string makeLog(const std::string &mess) = 0;
  virtual std::list<std::string>& getLogs() = 0;
};
