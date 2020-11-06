#include "ServerInterface.h"
#include <boost/asio.hpp>
#include <ostream>
#include <string>

const std::string STOP_CODE = ">exit<";
const std::string MESSAGE_END = "\n";

class MessageReciveServer : public ServerInterface {
public:
  MessageReciveServer(const short &readPort);
  void acceptConnection() override;
  void read(std::ostream &messOutput) override;
  void disconnected() override;
  std::string getMessage();

private:
  boost::asio::io_service m_ioService;
  boost::asio::ip::tcp::acceptor m_acceptorServer;
  boost::asio::ip::tcp::socket m_serverSocket;
};
