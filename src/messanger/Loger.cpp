#include "Loger.h"

Loger::Loger(const std::string &name) : m_username(name) {}

std::string Loger::makeLog(const std::string &mess) {
  std::string log = m_username + (": " + mess);
  std::lock_guard<std::mutex> logsLock(m_logsMutex);
  if (m_lastLogs.size() == 10)
    m_lastLogs.pop_back();
  m_lastLogs.push_front(log);
  return log;
}

std::list<std::string> &Loger::getLogs() {
  std::lock_guard<std::mutex> logsLock(m_logsMutex);
  return m_lastLogs;
}
