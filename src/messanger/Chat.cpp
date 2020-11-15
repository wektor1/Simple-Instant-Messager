#include "Chat.h"
#include "ComunicationExceptions.h"
#include <algorithm>
#include <cstdio>
#include <enumMenuStatus.h>
#include <future>
#include <iostream>
#include <string>

Chat::Chat(std::unique_ptr<MessSenderMangrInterface> &&messSender,
           std::unique_ptr<MessReciverMangrInterface> &&messReciver,
           std::unique_ptr<LogerInterface> &&loger,
           std::unique_ptr<ChatUIinterface> &&chatUI) noexcept
    : m_messSender(std::move(messSender)),
      m_messReciver(std::move(messReciver)), m_loger(std::move(loger)),
      m_ui(std::move(chatUI)) {}

bool Chat::establishConnection() {
  connectionMade.store(false);
  std::thread connection(&Chat::connectionLoop, this);
  auto connHandle = connection.native_handle();
  connection.detach();
  std::thread cancelation(&Chat::cancelConnection, this);
  auto cancelHandle = cancelation.native_handle();
  cancelation.detach();
  std::unique_lock<std::mutex> connectionLock(m_connectionMutex);
  m_connectionCondition.wait(connectionLock);
  pthread_cancel(connHandle);
  pthread_cancel(cancelHandle);
  return connectionMade.load();
}

void Chat::cancelConnection() {
  std::cout << "Press any key to cancel\n";
  getchar();
  m_connectionCondition.notify_all();
}

void Chat::connectionLoop() {
  auto reciverConnected = std::async(
      std::launch::async, &MessReciverMangrInterface::acceptConnection,
      m_messReciver.get());
  bool senderConnected = false;
  while (!senderConnected) {
    senderConnected = m_messSender->beginConnection();
  }
  reciverConnected.wait();
  connectionMade.store(true);
  m_connectionCondition.notify_all();
}

void Chat::readUntilDisconnected() {
  try {
    m_messReciver->continuousBufferRead();
  } catch (const ConnectionLostException &e) {
    endChat();
  } catch (const std::exception &e) {
    std::cout << e.what();
  }
}

void Chat::startReadingMessages() {
  auto readBuff =
      std::async(std::launch::async, &Chat::readUntilDisconnected, this);
  try {
    while (true) {
      std::string newMessage = m_messReciver->giveLastMessage();
      m_loger->addLog(newMessage);
      logsUpdate();
    }
  } catch (const std::exception &e) {
    readBuff.get();
  }
}

void Chat::logsUpdate() {
  m_ui->setLastLogs(m_loger->getLogs());
  drawUI();
}

void Chat::sendNewMessage(const std::string &mess) {
  auto snedingMessage = m_loger->makeSendLog(mess);
  m_messSender->createNewMessage(snedingMessage);
  logsUpdate();
}

void Chat::messageCreation() {
  std::string userMessage;
  std::getline(std::cin, userMessage);
  sendNewMessage(userMessage);
  m_menuStatus = MenuStatus::Menu;
  m_ui->setStatus(m_menuStatus);
}

void Chat::drawUI() { m_ui->draw(); }

void Chat::chatMenuLoop() {
  m_ui->setStatus(m_menuStatus);
  while (true) {
    drawUI();
    optionSelect();
  }
}

void Chat::optionSelect() {
  std::string input;
  std::getline(std::cin, input);
  try {
    int toInt = std::stoi(input);
    switch (toInt) {
    case 1:
      m_menuStatus = MenuStatus::Write;
      m_ui->setStatus(m_menuStatus);
      drawUI();
      messageCreation();
      break;
    case 2:
      sendNewMessage(">user quit<");
      endChat();
      break;
    }
  } catch (const std::invalid_argument &e) {
    std::cout << e.what();
  }
}

void Chat::openChat() {
  auto readingRecived =
      std::async(std::launch::async, &Chat::startReadingMessages, this);
  auto sendMess = std::async(
      std::launch::async, &MessSenderMangrInterface::continuousMessageSending,
      m_messSender.get());
  auto menu = std::async(std::launch::async, &Chat::chatMenuLoop, this);
  readingRecived.get();
}

void Chat::endChat() {
  m_messReciver->endConnection();
  m_messSender->endConnection();
  throw std::runtime_error("Chat ended by user");
}

std::unique_ptr<ChatInterface>
makeChat(std::unique_ptr<MessSenderMangrInterface> &&messSender,
         std::unique_ptr<MessReciverMangrInterface> &&messReciver,
         std::unique_ptr<LogerInterface> &&loger,
         std::unique_ptr<ChatUIinterface> &&chatUI) {
  return std::make_unique<Chat>(std::move(messSender), std::move(messReciver),
                                std::move(loger), std::move(chatUI));
}
