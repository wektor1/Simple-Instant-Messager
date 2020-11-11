#pragma once
#include "MessSenderMangrInterface.h"
#include <gmock/gmock.h>
#include <string>

class MockMessSenderMangrInterface : public MessSenderMangrInterface {
public:
  MOCK_METHOD(bool, beginConnection, (), (override));
  MOCK_METHOD(void, endConnection, (), (override));
  MOCK_METHOD(void, continuousMessageSending, (), (override));
  MOCK_METHOD(void, createNewMessage, (const std::string mess), (override));
};
