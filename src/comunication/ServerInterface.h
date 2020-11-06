#pragma once
#include <ostream>

class ServerInterface {
public:
  virtual ~ServerInterface(){};
  virtual void acceptConnection() = 0;
  virtual void read(std::ostream &messOutput) = 0;
  virtual void disconnected() = 0;
};
