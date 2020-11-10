#pragma once

#include <string>

class MessageHandlerInterface {
public:
  virtual ~MessageHandlerInterface(){}
  virtual bool messageInQueue() const = 0;
  virtual void messageToQueue(const std::string mess) = 0;
  virtual std::string takeMessageFromQueue() = 0;
};
