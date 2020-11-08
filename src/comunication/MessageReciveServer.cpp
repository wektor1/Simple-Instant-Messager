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

void MessageReciveServer::read(std::ostream &messOutput) {
  std::string response;
  while (true) {
    response = getMessage();
    if (response == STOP_CODE)
      disconnected();
    messOutput << response;
  }
}

void MessageReciveServer::disconnected() {
  throw ConnectionLostException("Client ended conversation");
}

std::string MessageReciveServer::getMessage() {
  boost::asio::streambuf buffer;
  boost::asio::read_until(m_serverSocket, buffer, MESSAGE_END);
  std::string data = boost::asio::buffer_cast<const char *>(buffer.data());
  data.pop_back();
  return data;
}
