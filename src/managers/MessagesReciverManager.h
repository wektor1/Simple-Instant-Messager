#include "MessageHandlerInterface.h"
#include "ServerInterface.h"
#include <memory>
#include <mutex>

class MessagesReciverManager {
public:
  MessagesReciverManager(ServerInterface *messageSender,
                         MessageHandlerInterface *messageHandler) noexcept;
  bool acceptConnection();
  void continuousBufferRead();

private:
  std::unique_ptr<ServerInterface> m_messageReciver;
  std::unique_ptr<MessageHandlerInterface> m_messageHandler;
  std::mutex m_messHandlerMutex;
};
