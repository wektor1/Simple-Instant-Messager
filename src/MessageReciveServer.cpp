#include "MessageReciveServer.h"

MessageReciveServer::MessageReciveServer(const short &readPort)
    : BaseServer(readPort) {}

void MessageReciveServer::readMessages() {
  std::string response;
  while (true) {
    response = getData(getSocket());
    if (response == STOP_CODE)
      break;
  }
}

std::string MessageReciveServer::getData(boost::asio::ip::tcp::socket& serverSocket) {
  boost::asio::streambuf buffer;
  boost::asio::read_until(serverSocket, buffer, MESSAGE_END);
  std::string data = boost::asio::buffer_cast<const char *>(buffer.data());
  data.pop_back();
  return data;
}
