#include "ClientInterface.h"
#include <gmock/gmock.h>

class MockClientInterface : public ClientInterface {
public:
  MOCK_METHOD(void, connect, (), (override));
  virtual void send(std::ostream &messOutput, const std::string &message) {
    messOutput << message;
  }
  MOCK_METHOD(void, disconnect, (), (override));
};
