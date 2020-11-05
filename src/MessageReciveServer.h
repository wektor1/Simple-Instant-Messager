#include "BaseServer.h"
#include <boost/asio.hpp>
#include <iostream>
#include <string>

const auto STOP_CODE = ">exit<";
const auto MESSAGE_END = "\n";

class MessageReciveServer : public BaseServer {
public:
  MessageReciveServer(const short &readPort);
  void readMessages();
  std::string getData(boost::asio::ip::tcp::socket& serverSocket);
};
