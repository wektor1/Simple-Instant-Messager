#include "ServerInterface.h"
#include <gmock/gmock.h>
#include "ComunicationExceptions.h"

class MockServerInterface : public ServerInterface {
public:
  MOCK_METHOD(void, acceptConnection, (), (override));
  MOCK_METHOD(void, read, (std::ostream &messOutput), (override));
  virtual void disconnected() {
    throw ConnectionLostException("Client ended conversation");
  }
};
