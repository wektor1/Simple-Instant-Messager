#pragma once
#include <string>

class ChatInterface {
public:
  virtual ~ChatInterface() {}
  virtual bool establishConnection() = 0;
  virtual void openChat() = 0;
  virtual void startReadingMessages() = 0;
  virtual void sendNewMessage(const std::string &mess) = 0;
};
