#pragma once
#include <memory>
#include <ostream>
#include <string>

class ClientInterface {
public:
  virtual ~ClientInterface() = default;
  virtual void connect() = 0;
  virtual void send(const std::string &message) = 0;
  virtual void disconnect() = 0;
};

std::unique_ptr<ClientInterface>
makeMessageSendClient(const std::string &hostAddress, const short &hostPort);
