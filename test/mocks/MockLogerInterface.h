#pragma once
#include <LogerInterface.h>
#include <string>
#include <list>
#include <gmock/gmock.h>

class MockLogerInterface : public LogerInterface {
public:
  MOCK_METHOD(std::string, makeSendLog, (const std::string &mess), (override));
  MOCK_METHOD(void, addLog, (const std::string &mess), (override));
  MOCK_METHOD(std::list<std::string>&, getLogs, (), (override));
};
