#pragma once
#include <fstream>
#include <string>
#include <memory>
#include "Chat.h"

class MainScreen {
public:
  MainScreen();
  void startApp();

private:
  std::string m_name = "";
  std::string m_scndUserAddress = "";
  short m_readPort = 0;
  short m_destinationPort = 0;
  void showOptions();
  void clearScreen();
  void configFromFile();
  void configFromInput();
  void readFile(std::ifstream &file);
  short inputValidator(const std::string &errMess);
  void configToFile();
  void openChat();
  std::unique_ptr<Chat> makeChat(std::string scndUserAddress, short readPort,
                                 short scndUserPort, std::string name);
  void writeToFile(std::ofstream &file);
};
