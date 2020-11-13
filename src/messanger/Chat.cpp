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
           ChatUIinterface *chatUI, TimerInterface *timer) noexcept
    : m_messSender(std::move(messSender)),
      m_messReciver(std::move(messReciver)), m_loger(std::move(loger)),
      m_ui(std::move(chatUI)), m_timer(std::move(timer)) {}

bool Chat::establishConnection() {
  auto reciverConnected =
      std::async(std::launch::async, &Chat::tryUntilTimeout, this,
                 std::bind(&Chat::tryAcceptConnection, this));
  auto senderConnected =
      std::async(std::launch::async, &Chat::tryUntilTimeout, this,
                 std::bind(&Chat::tryBeginConnection, this));
  if (!senderConnected.get() || !reciverConnected.get())
    return false;
  return true;;
}

bool Chat::tryUntilTimeout(std::function<bool()> conn) {
  auto currentTime = m_timer->currentTime();
  auto finishTime = m_timer->finishTime(10s);
  while (currentTime < finishTime) {
    auto result = conn();
    if (result)
      return true;
    currentTime = m_timer->currentTime();
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
      m_timer->sleep(1s);
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
  throw std::runtime_error("Chat ended by user");
}
