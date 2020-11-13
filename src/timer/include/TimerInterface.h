#pragma once
#include <chrono>

class TimerInterface {
public:
  virtual ~TimerInterface() {}
  virtual void sleep(const std::chrono::seconds &duration) = 0;
  virtual std::chrono::time_point<std::chrono::system_clock> currentTime() = 0;
  virtual std::chrono::time_point<std::chrono::system_clock>
  finishTime(const std::chrono::seconds &duration) = 0;
};
