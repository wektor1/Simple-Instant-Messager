#include "ClientInterface.h"
#include <gmock/gmock.h>

class MockClientInterface : public ClientInterface {
public:
  MOCK_METHOD(void, connect, (), (override));
  MOCK_METHOD(void, send, (const std::string &message), (override));
  MOCK_METHOD(void, disconnect, (), (override));
};
