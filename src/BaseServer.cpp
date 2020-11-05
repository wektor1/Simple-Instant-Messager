#include "BaseServer.h"

BaseServer::BaseServer(const short &readPort)
    : m_ioService(),
      m_acceptorServer(m_ioService, boost::asio::ip::tcp::endpoint(
                                        boost::asio::ip::tcp::v4(), readPort)),
      m_serverSocket(m_ioService) {
  m_acceptorServer.accept(m_serverSocket);
}

BaseServer::~BaseServer() {}

boost::asio::ip::tcp::socket &BaseServer::getSocket() { return m_serverSocket; }
