#pragma once
#include <ostream>

class ServerInterface {
public:
  virtual ~ServerInterface(){};
  virtual void acceptConnection() = 0;
  virtual std::string read() = 0;
  virtual void disconnected() = 0;
};
