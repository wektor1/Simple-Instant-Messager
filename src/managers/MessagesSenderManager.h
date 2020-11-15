#include "ClientInterface.h"
#include "MessSenderMangrInterface.h"
#include "MessageHandlerInterface.h"
#include <condition_variable>
#include <memory>
#include <mutex>
#include <string>

class MessagesSenderManager : public MessSenderMangrInterface {
public:
  MessagesSenderManager(ClientInterface *messageSender,
                        MessageHandlerInterface *messageHandler) noexcept;
  bool beginConnection() override;
  void endConnection() override;
  void createNewMessage(const std::string mess) override;
  void continuousMessageSending() override;

private:
  std::unique_ptr<ClientInterface> m_messageSender;
  std::unique_ptr<MessageHandlerInterface> m_messageHandler;
  std::mutex m_messHandlerMutex;
  std::condition_variable m_conditionInQueue;
  bool m_connectionValid;
  void sendMessageInQueue();
};
