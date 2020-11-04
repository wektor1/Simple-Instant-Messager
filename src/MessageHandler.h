#include <queue>
#include <string>

class MessageHandler {
public:
  bool messageInQueue() const;
  void messageToSend(const std::string mess);
  std::string processFirst();

private:
  std::queue<std::string> m_messagesQueue;
};
