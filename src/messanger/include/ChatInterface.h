#pragma once
#include "ChatUIinterface.h"
#include "ClientInterface.h"
#include "LogerInterface.h"
#include "MessReciverMangrInterface.h"
#include "MessSenderMangrInterface.h"
#include "MessageHandlerInterface.h"
#include "ServerInterface.h"
#include <memory>
#include <string>

class ChatInterface {
public:
  virtual ~ChatInterface() = default;
  virtual bool establishConnection() = 0;
  virtual void openChat() = 0;
  virtual void startReadingMessages() = 0;
  virtual void sendNewMessage(const std::string &mess) = 0;
};

std::unique_ptr<ChatInterface>
makeChat(std::unique_ptr<MessSenderMangrInterface> &&messSender,
         std::unique_ptr<MessReciverMangrInterface> &&messReciver,
         std::unique_ptr<LogerInterface> &&loger,
         std::unique_ptr<ChatUIinterface> &&chatUI);
