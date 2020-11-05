#include "MessageSendClient.h"

MessageSendClient::MessageSendClient(const std::string &hostAddress,
                                     const short &hostPort)
    : BaseClient(hostAddress, hostPort) {}

void MessageSendClient::sendMessages(std::ostream &messOutput,
                                     const std::string &message) {
  boost::asio::write(getSocket(), boost::asio::buffer(message + MESSAGE_END));
  messOutput << message;
}
