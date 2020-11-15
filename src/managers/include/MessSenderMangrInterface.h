#pragma once
#include "ClientInterface.h"
#include "MessageHandlerInterface.h"
#include <memory>
#include <string>

class MessSenderMangrInterface {
public:
  virtual ~MessSenderMangrInterface() = default;
  virtual bool beginConnection() = 0;
  virtual void endConnection() = 0;
  virtual void createNewMessage(const std::string mess) = 0;
  virtual void continuousMessageSending() = 0;
};

std::unique_ptr<MessSenderMangrInterface> makeMessSenderManager(
    std::unique_ptr<ClientInterface> &&messageSender,
    std::unique_ptr<MessageHandlerInterface> &&messageHandler);
