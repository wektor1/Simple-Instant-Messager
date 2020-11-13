#include "ClientInterface.h"
#include "MessSenderMangrInterface.h"
#include "MessageHandlerInterface.h"
#include "TimerInterface.h"
#include <memory>
#include <mutex>
#include <string>

class MessagesSenderManager : public MessSenderMangrInterface {
public:
  MessagesSenderManager(ClientInterface *messageSender,
                        MessageHandlerInterface *messageHandler,
                        TimerInterface *timer) noexcept;
  bool beginConnection() override;
  void endConnection() override;
  void createNewMessage(const std::string mess) override;
  void continuousMessageSending() override;

private:
  std::unique_ptr<ClientInterface> m_messageSender;
  std::unique_ptr<MessageHandlerInterface> m_messageHandler;
  std::unique_ptr<TimerInterface> m_timer;
  std::mutex m_messHandlerMutex;
  bool m_connectionValid;
  void sendMessageInQueue();
};
