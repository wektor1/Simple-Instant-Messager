#pragma once
#include <ostream>
#include <string>

class ClientInterface {
public:
  virtual ~ClientInterface(){};
  virtual void connect() = 0;
  virtual void send(std::ostream &messOutput, const std::string &message) = 0;
  virtual void disconnect() = 0;
};
