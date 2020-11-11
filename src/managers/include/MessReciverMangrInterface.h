#pragma once
#include <string>

class MessReciverMangrInterface {
public:
  virtual ~MessReciverMangrInterface() {}
  virtual bool acceptConnection() = 0;
  virtual void endConnection() = 0;
  virtual void continuousBufferRead() = 0;
  virtual std::string giveLastMessage() = 0;
};
