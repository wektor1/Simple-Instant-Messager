#include <queue>
#include <string>

class MessageHandler {
public:
  bool messageInQueue();

private:
  std::queue<std::string> m_messagesQueue;
};
