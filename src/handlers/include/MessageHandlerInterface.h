#pragma once
#include <memory>
#include <string>

class MessageHandlerInterface {
public:
  virtual ~MessageHandlerInterface() = default;
  virtual bool messageInQueue() const = 0;
  virtual void messageToQueue(const std::string mess) = 0;
  virtual std::string takeMessageFromQueue() = 0;
};

std::unique_ptr<MessageHandlerInterface> makeMessageHandler();
