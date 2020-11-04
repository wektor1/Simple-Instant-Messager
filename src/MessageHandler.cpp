#include "MessageHandler.h"

bool MessageHandler::messageInQueue() { return !m_messagesQueue.empty(); }
