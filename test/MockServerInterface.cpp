#include "ServerInterface.h"
#include <gmock/gmock.h>

class MockServerInterface : public ServerInterface {
public:
  MOCK_METHOD(void, acceptConnection, (), (override));
  MOCK_METHOD(std::string, read, (), (override));
  MOCK_METHOD(void, disconnected, (), (override));
};
