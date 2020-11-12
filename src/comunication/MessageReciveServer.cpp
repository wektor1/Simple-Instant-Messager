#include "MessageReciveServer.h"
#include "ComunicationExceptions.h"
#include "MessagesDefinitions.h"

MessageReciveServer::MessageReciveServer(const short &readPort)
    : m_ioService(),
      m_acceptorServer(m_ioService, boost::asio::ip::tcp::endpoint(
                                        boost::asio::ip::tcp::v4(), readPort)),
      m_serverSocket(m_ioService) {}

void MessageReciveServer::acceptConnection() {
  m_acceptorServer.accept(m_serverSocket);
}

std::string MessageReciveServer::read() {
  std::string response;
  response = getMessage();
  if (response + "\n" == STOP_CODE)
    disconnected();
  return response;
}

void MessageReciveServer::disconnected() {
  throw ConnectionLostException("Client ended conversation");
}

std::string MessageReciveServer::getMessage() {
  boost::asio::streambuf buffer;
  auto len = boost::asio::read_until(m_serverSocket, buffer, MESSAGE_END);
  std::string data = boost::asio::buffer_cast<const char *>(buffer.data());
  return data.substr(0, len - 1);
}
