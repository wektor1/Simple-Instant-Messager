#include "ClientInterface.h"
#include <boost/asio.hpp>
#include <ostream>
#include <string>

class MessageSendClient : public ClientInterface {
public:
  MessageSendClient(const std::string &hostAddress, const short &hostPort);
  void connect() override;
  void send(const std::string &message) override;
  void sendMessage(const boost::asio::const_buffer &buff);
  void disconnect() override;

private:
  boost::asio::io_service m_ioService;
  boost::asio::ip::tcp::socket m_clientSocket;
  std::string m_hostAddress;
  short m_hostPort;
};
