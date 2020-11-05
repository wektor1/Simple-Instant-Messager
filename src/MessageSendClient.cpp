#include "MessageSendClient.h"

MessageSendClient::MessageSendClient(const std::string &hostAddress,
                                     const short &hostPort)
    : BaseClient(hostAddress, hostPort) {}

void MessageSendClient::prepareData(std::ostream &messOutput,
                                    const std::string &message) {
  sendMessage(getSocket(), boost::asio::buffer(message + MESSAGE_END));
  messOutput << message;
}

void MessageSendClient::sendMessage(boost::asio::ip::tcp::socket &hostSocket,
                                    const boost::asio::const_buffer &buff) {
  boost::asio::write(hostSocket, buff);
}
