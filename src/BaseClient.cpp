#include "BaseClient.h"

BaseClient::BaseClient(const std::string &hostAddress, const short &hostPort)
    : m_ioService(), m_clientSocket(m_ioService) {
  m_clientSocket.connect(boost::asio::ip::tcp::endpoint(
      boost::asio::ip::address::from_string("127.0.0.1"), hostPort));
}

BaseClient::~BaseClient() {}

boost::asio::ip::tcp::socket &BaseClient::getSocket() { return m_clientSocket; }
