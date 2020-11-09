#include "MessageHandlerInterface.h"
#include <gmock/gmock.h>
#include <string>

class MockMessageHandlerInterface : public MessageHandlerInterface {
public:
  MOCK_METHOD(bool, messageInQueue, (), (const override));
  MOCK_METHOD(void, messageToQueue, (const std::string message), (override));
  MOCK_METHOD(std::string, messageToSend, (), (override));
};
