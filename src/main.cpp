#include "Chat.h"
#include "MessageHandler.h"
#include "MessageReciveServer.h"
#include "MessageSendClient.h"
#include "MessagesReciverManager.h"
#include "MessagesSenderManager.h"
#include <cstdio>
#include <iostream>
#include <memory>
#include <string>

std::unique_ptr<Chat> makeChat(std::string scndUserAddress, short readPort,
                               short scndUserPort, std::string name) {
  MessageReciveServer *messServ(new MessageReciveServer(readPort));
  MessageSendClient *messClt(
      new MessageSendClient(scndUserAddress, scndUserPort));
  MessagesReciverManager *recMgr(
      new MessagesReciverManager(messServ, new MessageHandler()));
  MessagesSenderManager *sendMgr(
      new MessagesSenderManager(messClt, new MessageHandler()));
  return std::make_unique<Chat>(sendMgr, recMgr, name);
}

int main(int argc, char **argv) {
  std::unique_ptr<Chat> p1;
  char selectOption = getchar();
  if (selectOption == '1') {
    std::cout << "1";
    p1 = makeChat("192.168.0.66", 1025, 1026, "Host 1");
  } else if (selectOption == '2') {
    std::cout << "2";
    p1 = makeChat("192.168.0.66", 1026, 1025, "Host 2");
  }
  if (p1->establishConnection()) {
    std::cout << "Connected";
    p1->openChat();
  }
  return 0;
}
