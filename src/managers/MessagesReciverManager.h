#include "MessReciverMangrInterface.h"
#include "MessageHandlerInterface.h"
#include "ServerInterface.h"
#include <memory>
#include <condition_variable>
#include <mutex>
#include <string>

class MessagesReciverManager : public MessReciverMangrInterface {
public:
  MessagesReciverManager(ServerInterface *messageSender,
                         MessageHandlerInterface *messageHandler) noexcept;
  bool acceptConnection() override;
  void continuousBufferRead() override;
  void endConnection() override;
  std::string giveLastMessage() override;

private:
  std::unique_ptr<ServerInterface> m_messageReciver;
  std::unique_ptr<MessageHandlerInterface> m_messageHandler;
  std::condition_variable m_conditionInQueue;
  bool m_connectionValid;
  std::mutex m_messHandlerMutex;
};
