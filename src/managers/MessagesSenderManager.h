#include "ClientInterface.h"
#include "MessageHandlerInterface.h"
#include <memory>
#include <mutex>
#include <string>

class MessagesSenderManager {
public:
  MessagesSenderManager(ClientInterface *messageSender,
                        MessageHandlerInterface *messageHandler) noexcept;
  bool beginConnection();
  void endConnection();
  void createNewMessage(const std::string mess);
  void continuousMessageSending();

private:
  std::unique_ptr<ClientInterface> m_messageSender;
  std::unique_ptr<MessageHandlerInterface> m_messageHandler;
  std::mutex m_messHandlerMutex;
  bool m_connectionValid;
  void sendMessageInQueue();
};
