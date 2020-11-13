#include "TimerInterface.h"
#include <thread>

class Timer : public TimerInterface {
public:
  void sleep(const std::chrono::seconds &duration) override {
    std::this_thread::sleep_for(duration);
  }
  std::chrono::time_point<std::chrono::system_clock> currentTime() override {
    return std::chrono::system_clock::now();
  }
  std::chrono::time_point<std::chrono::system_clock>
  finishTime(const std::chrono::seconds &duration) override {
    return std::chrono::system_clock::now() + duration;
  }
};
