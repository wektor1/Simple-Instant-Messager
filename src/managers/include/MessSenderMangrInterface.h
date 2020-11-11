#pragma once
#include <string>

class MessSenderMangrInterface {
public:
  virtual ~MessSenderMangrInterface() {}
  virtual bool beginConnection() = 0;
  virtual void endConnection() = 0;
  virtual void createNewMessage(const std::string mess) = 0;
  virtual void continuousMessageSending() = 0;
};
