#pragma once
#include "ChatUIinterface.h"
#include "enumMenuStatus.h"
#include <list>
#include <string>
#include <gmock/gmock.h>

class MockChatUIinterface : public ChatUIinterface {
public:
  MOCK_METHOD(void, draw, (), (override));
  MOCK_METHOD(void, setStatus, (const MenuStatus &status), (override));
  MOCK_METHOD(void, setLastLogs, (const std::list<std::string> &logs), (override));
};
