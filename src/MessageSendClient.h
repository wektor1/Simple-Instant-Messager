#include "BaseClient.h"
#include <boost/asio.hpp>
#include <ostream>
#include <string>

const auto MESSAGE_END = "\n";

class MessageSendClient : public BaseClient {
public:
  MessageSendClient(const std::string &hostAddress, const short &hostPort);
  void prepareData(std::ostream &messOutput, const std::string &message);
  void sendMessage(boost::asio::ip::tcp::socket &hostSocket,
                   const boost::asio::const_buffer &buff);
};
