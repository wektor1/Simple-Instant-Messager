#pragma once
#include <ostream>
#include <memory>

class ServerInterface {
public:
  virtual ~ServerInterface() = default;
  virtual void acceptConnection() = 0;
  virtual std::string read() = 0;
  virtual void disconnected() = 0;
};

std::unique_ptr<ServerInterface> makeMessageReciveServer(const short &readPort);
