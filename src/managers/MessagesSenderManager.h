#include "ClientInterface.h"
#include "MessageHandlerInterface.h"
#include <memory>
#include <mutex>
#include <string>

class MessagesSenderManager {
public:
  MessagesSenderManager(ClientInterface *messageSender,
                        MessageHandlerInterface *messageHandler) noexcept;
  void createNewMessage(const std::string mess);
  bool beginConnection();
  void endConnection();
  void continuousMessageSending();

private:
  std::unique_ptr<ClientInterface> m_messageSender;
  std::unique_ptr<MessageHandlerInterface> m_messageHandler;
  std::mutex m_messHandlerMutex;
  bool m_connectionValid;
};
