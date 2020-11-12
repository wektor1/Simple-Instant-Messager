#include "Chat.h"
#include "ComunicationExceptions.h"
#include <algorithm>
#include <chrono>
#include <enumMenuStatus.h>
#include <future>
#include <iostream>
#include <string>

using namespace std::chrono_literals;

Chat::Chat(MessSenderMangrInterface *messSender,
           MessReciverMangrInterface *messReciver, LogerInterface *loger,
           ChatUIinterface *chatUI) noexcept
    : m_messSender(std::move(messSender)),
      m_messReciver(std::move(messReciver)), m_loger(std::move(loger)),
      m_ui(std::move(chatUI)) {}

bool Chat::establishConnection() {
  auto reciverConnected =
      std::async(std::launch::async, &Chat::tryUntilTimeout, this,
                 std::bind(&Chat::tryAcceptConnection, this));
  auto senderConnected =
      std::async(std::launch::async, &Chat::tryUntilTimeout, this,
                 std::bind(&Chat::tryBeginConnection, this));
  if (reciverConnected.get() && senderConnected.get())
    return true;
  return false;
}

bool Chat::tryUntilTimeout(std::function<bool()> conn) {
  auto start_time = std::chrono::system_clock::now();
  auto current_time = start_time;
  while (current_time < start_time + 10s) {
    auto result = conn();
    if (result)
      return true;
    current_time = std::chrono::system_clock::now();
  }
  return false;
}

bool Chat::tryAcceptConnection() { return m_messReciver->acceptConnection(); }

bool Chat::tryBeginConnection() { return m_messSender->beginConnection(); }

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
      logsUpdate(newMessage);
    }
  } catch (const std::exception &e) {
    readBuff.get();
  }
}

std::string Chat::logsUpdate(const std::string &mess) {
  auto log = m_loger->makeLog(mess);
  m_ui->setLastLogs(m_loger->getLogs());
  return log;
}

void Chat::sendNewMessage(const std::string &mess) {
  m_messSender->createNewMessage(logsUpdate(mess));
  drawUI();
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
      std::this_thread::sleep_for(1s);
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
  m_messSender->endConnection();
  m_messReciver->endConnection();
  throw std::runtime_error("Temporary except for chat ending");
}
