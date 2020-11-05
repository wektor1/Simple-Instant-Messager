#include <boost/asio.hpp>
#include <string>

class BaseClient {
public:
  BaseClient(const std::string &hostAddress, const short &hostPort);
  virtual ~BaseClient();
  boost::asio::ip::tcp::socket &getSocket();

private:
  boost::asio::io_service m_ioService;
  boost::asio::ip::tcp::socket m_clientSocket;
};
