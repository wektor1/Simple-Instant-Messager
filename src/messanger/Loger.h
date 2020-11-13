#pragma once
#include "LogerInterface.h"
#include <list>
#include <string>
#include <mutex>

class Loger : public LogerInterface {
public:
  Loger(const std::string &name);
  std::string makeSendLog(const std::string &mess) override;
  void addLog(const std::string &mess) override;
  std::list<std::string>& getLogs() override;
private:
  std::string m_username;
  std::mutex m_logsMutex;
  std::list<std::string> m_lastLogs;
};
