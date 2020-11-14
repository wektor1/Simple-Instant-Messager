#include "MainScreen.h"
#include "Chat.h"
#include "ChatUI.h"
#include "Loger.h"
#include "MessageHandler.h"
#include "MessageReciveServer.h"
#include "MessageSendClient.h"
#include "MessagesReciverManager.h"
#include "MessagesSenderManager.h"
#include "Timer.cpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

MainScreen::MainScreen() {}

void MainScreen::startApp() {
  bool exit = false;
  while (!exit) {
    showOptions();

    try {
      auto option = inputValidator("Is not proper number");
      switch (option) {
      case 1:
        configFromFile();
        break;
      case 2:
        configFromInput();
        break;
      case 3:
        openChat();
        exit = true;
        break;
      case 4:
        exit = true;
        break;
      }
    } catch (const std::exception &e) {
      showStatusInfo("ERROR :", e.what());
    }
  }
}

void MainScreen::showStatusInfo(const std::string &statusType,
                                const std::string &statusMessage) {
  clearScreen();
  std::cout << statusType << statusMessage << "\n";
}

void MainScreen::showOptions() {
  std::cout << "Select operation:\n"
            << "1-Load data from file (last input data)\n"
            << "2-Enter new data\n"
            << "3-Begin chat\n"
            << "4-Close aplication\n"
            << "Type: ";
}

void MainScreen::clearScreen() { std::cout << std::string(100, '\n'); }

void MainScreen::configFromFile() {
  std::filesystem::path dir = "configs";
  std::filesystem::path file = "configs/Config.txt";
  if (std::filesystem::exists(dir) && std::filesystem::exists(file) &&
      std::filesystem::is_regular_file(file)) {
    std::ifstream config;
    config.open(file.string());
    readFile(config);
    config.close();
  } else {
    throw std::invalid_argument("This is first use");
  }
  showStatusInfo("Status :", "Loading from file finished");
}

void MainScreen::readFile(std::ifstream &file) {
  if (file.is_open()) {
    std::getline(file, m_name);
    std::getline(file, m_scndUserAddress);
    std::string tempPort;
    std::getline(file, tempPort);
    m_readPort = std::stoi(tempPort);
    std::getline(file, tempPort);
    m_destinationPort = std::stoi(tempPort);
  } else {
    throw std::runtime_error("Couldn't open file");
  }
}

short MainScreen::inputValidator(const std::string &errMess) {
  short toInt;
  std::string input;
  std::getline(std::cin, input);
  try {
    toInt = std::stoi(input);

  } catch (const std::invalid_argument &e) {
    throw std::invalid_argument(errMess);
  }
  return toInt;
}

void MainScreen::configFromInput() {
  clearScreen();
  std::cout << "Type your username:\n";
  std::getline(std::cin, m_name);
  std::cout << "Type connection address:\n";
  std::getline(std::cin, m_scndUserAddress);
  std::cout << "Type your reading port:\n";
  m_readPort = inputValidator("Bad port typed");
  std::cout << "Type your destination port:\n";
  m_destinationPort = inputValidator("Bad port typed");
  configToFile();
  showStatusInfo("Status :", "Data from input saved");
}

void MainScreen::configToFile() {
  std::filesystem::path dir = "configs";
  std::filesystem::path file = "configs/Config.txt";
  if (std::filesystem::exists(dir) && std::filesystem::is_directory(dir)) {
    if (std::filesystem::exists(file) &&
        std::filesystem::is_regular_file(file)) {
      std::ofstream config;
      config.open(file.string(), std::ofstream::trunc);
      writeToFile(config);
      config.close();
    } else {
      std::ofstream(file.string());
    }
  } else {
    std::filesystem::create_directory(dir);
    std::ofstream(file.string());
  }
}

void MainScreen::writeToFile(std::ofstream &file) {
  file << m_name << "\n"
       << m_scndUserAddress << "\n"
       << m_readPort << "\n"
       << m_destinationPort << "\n";
}

void MainScreen::openChat() {
  std::unique_ptr<Chat> p1 =
      makeChat(m_scndUserAddress, m_readPort, m_destinationPort, m_name);
  if (p1->establishConnection()) {
    std::cout << "Connected";
    try {
      p1->openChat();
    } catch (const std::exception &e) {
      clearScreen();
      std::cout << e.what() << "\n";
    }
  }
}

std::unique_ptr<Chat> MainScreen::makeChat(std::string scndUserAddress,
                                           short readPort, short scndUserPort,
                                           std::string name) {
  MessageReciveServer *messServ(new MessageReciveServer(readPort));
  MessageSendClient *messClt(
      new MessageSendClient(scndUserAddress, scndUserPort));
  MessagesReciverManager *recMgr(
      new MessagesReciverManager(messServ, new MessageHandler(), new Timer()));
  MessagesSenderManager *sendMgr(
      new MessagesSenderManager(messClt, new MessageHandler(), new Timer()));
  Loger *loger(new Loger(name));
  ChatUI *ui(new ChatUI());
  Timer *tmr(new Timer());
  return std::make_unique<Chat>(sendMgr, recMgr, loger, ui, tmr);
}
