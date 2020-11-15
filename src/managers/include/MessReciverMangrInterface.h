#pragma once
#include "MessageHandlerInterface.h"
#include "ServerInterface.h"
#include <memory>
#include <string>

class MessReciverMangrInterface {
public:
  virtual ~MessReciverMangrInterface() = default;
  virtual bool acceptConnection() = 0;
  virtual void endConnection() = 0;
  virtual void continuousBufferRead() = 0;
  virtual std::string giveLastMessage() = 0;
};

std::unique_ptr<MessReciverMangrInterface> makeMessReciverManager(
    std::unique_ptr<ServerInterface> &&messageReciver,
    std::unique_ptr<MessageHandlerInterface> &&messageHandler);
