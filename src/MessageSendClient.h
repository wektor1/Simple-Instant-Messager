#include "BaseClient.h"
#include <boost/asio.hpp>
#include <ostream>
#include <string>

const auto MESSAGE_END = "\n";

class MessageSendClient : public BaseClient {
public:
  MessageSendClient(const std::string &hostAddress, const short &hostPort);
  void sendMessages(std::ostream &messOutput, const std::string &message);
};
