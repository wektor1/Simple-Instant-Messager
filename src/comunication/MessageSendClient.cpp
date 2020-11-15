#include "MessageSendClient.h"
#include "MessagesDefinitions.h"

MessageSendClient::MessageSendClient(const std::string &hostAddress,
                                     const short &hostPort)
    : m_ioService(), m_clientSocket(m_ioService), m_hostAddress(hostAddress),
      m_hostPort(hostPort) {}

void MessageSendClient::connect() {
  m_clientSocket.connect(boost::asio::ip::tcp::endpoint(
      boost::asio::ip::address::from_string(m_hostAddress), m_hostPort));
}

void MessageSendClient::send(const std::string &message) {
  sendMessage(boost::asio::buffer(message + MESSAGE_END));
}

void MessageSendClient::sendMessage(const boost::asio::const_buffer &buff) {
  boost::asio::write(m_clientSocket, buff);
}

void MessageSendClient::disconnect() {
  send(STOP_CODE);
}

std::unique_ptr<ClientInterface>
makeMessageSendClient(const std::string &hostAddress, const short &hostPort){
  return std::make_unique<MessageSendClient>(hostAddress, hostPort);
}

