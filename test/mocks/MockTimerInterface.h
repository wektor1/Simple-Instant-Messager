#pragma once
#include "TimerInterface.h"

class MockTimerInterface : public TimerInterface {
public:
  MOCK_METHOD(void, sleep, (const std::chrono::seconds &duration), (override));
  MOCK_METHOD(std::chrono::time_point<std::chrono::system_clock>, currentTime,
              (), (override));
  MOCK_METHOD(std::chrono::time_point<std::chrono::system_clock>, finishTime,
              (const std::chrono::seconds &duration), (override));
};
