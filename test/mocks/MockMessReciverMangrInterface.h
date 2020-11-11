#pragma once
#include "MessReciverMangrInterface.h"
#include <gmock/gmock.h>
#include <string>

class MockMessReciverMangrInterface : public MessReciverMangrInterface {
public:
  MOCK_METHOD(bool, acceptConnection, (), (override));
  MOCK_METHOD(void, endConnection, (), (override));
  MOCK_METHOD(void, continuousBufferRead, (), (override));
  MOCK_METHOD(std::string, giveLastMessage, (), (override));
};
