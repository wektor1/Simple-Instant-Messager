#pragma once
#include <boost/asio.hpp>
#include <iostream>
#include <string>

class BaseServer
{
public:
  BaseServer(const short &readPort);
  boost::asio::ip::tcp::socket& getSocket();

private:
  boost::asio::io_service m_ioService;
  boost::asio::ip::tcp::acceptor m_acceptorServer;
  boost::asio::ip::tcp::socket m_serverSocket;
};
